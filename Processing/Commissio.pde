import SimpleOpenNI.*;
SimpleOpenNI kinect;
import se.goransson.mqtt.*;

MQTT mqtt;
int[] user1 = {
  235,137,62}; 
int[] user1pos = {
  100,100, 0};
int user1count = 0;

int sceneHeight = 300;
int sceneWidth = 400;

int xRound;
int yRound;
int zRound;
int proximeter = 5;
int stopmove = proximeter;

//Required Trust levels before user turns green
int trust = 0;
int requiredTrust = 1; //Requires 

//Timer before trust point
int timer = 0;
int timeLimit = 100;
int dot = 0;

//User Trust
int []usertrusted = {
  0, 0, 0, 0, 0};

//Global Kinect Variables
IntVector userList;
PVector position;
int userId = 0;
Float []zAxsis = {
  2.4, 4.8, 7.2, 9.6, 12.0, 14.4, 16.8, 19.2, 21.6, 24.0, 26.4, 28.8, 31.2, 33.6};
int datanumber;

//LED Grid
int[] LED = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int grid;
int lednumb;

PFont mono;

String[] lines;
int index = 0;
int timer2 = 0;
int timeLimit2 = 4;

void setup(){
  //Kinect Setup
  kinect = new SimpleOpenNI(this);
  kinect.setMirror(true);
  kinect.enableDepth();
  kinect.enableUser(SimpleOpenNI.SKEL_PROFILE_NONE);

  //MQTT setup
  mqtt = new MQTT(this);
  mqtt.connect("127.0.0.1", 1883, "Kinect");
  mqtt.publish("Kinect", "Tracking");

  //General Setup
  sceneHeight = kinect.depthHeight();
  sceneWidth = kinect.depthWidth();
  size(sceneWidth, sceneHeight);
  frame.setBackground(new java.awt.Color(0,0,0));
  background(0);
  mono = loadFont("HelveticaNeue-UltraLight-9.vlw");
  lednumb = 15;
  
  //Grid Setup
  grid = sceneWidth/lednumb;
  for(int i=0; i<14; i++){
    LED[i] = grid*(i+1);
  }
  
  //Data Setup
  lines = loadStrings("radiation.txt");
}

void draw(){
  background(0);
  textSize(2);
  textFont(mono);
  fill(255, 255, 255, 50);
  text(("Timer:  " + timer), 10, (sceneHeight-10));
  text(("Trust:  " + trust), 10, (sceneHeight-20));
  text(("Data:  " + datanumber), 10, (sceneHeight-30));

  kinect.update();

  //Pulling in data
  if (userId <= 0 || usertrusted[0] == 1){
    timer2++;
    if (timer2 == timeLimit2){
      if (index < lines.length) {
        String[] pieces = split(lines[index], '\t');
        if (pieces.length == 1) {
          int x = int(pieces[0]) * 2;
          datanumber = Integer.parseInt(pieces[0]);
          if (datanumber <15){
            mqtt.publish("Kinect", ("Data" + datanumber));
          }
        }
        index = index + 1;
      }else if(index == lines.length){
        index=0;
      }
      timer2 = 0;
    }
  }
  
  //Load Kinect Tracking Users
  userList = new IntVector();
  kinect.getUsers(userList);
  for (int i=0; i<userList.size(); i++){
    userId = userList.get(i);
    position = new PVector();
    kinect.getCoM(userId, position);
    kinect.convertRealWorldToProjective(position, position);
    if (userId == 0){
      println("reseting users");
      for(int a=0; a<2; a++){
        user1pos[a] = 0;
      }
    }
    xRound = round(position.x);
    yRound = round(position.y);
    zRound = round(position.z/100);

    //Track user 1
    if (userId == 1){
      fill(user1[0],user1[1],user1[2]);
      trackUser(zRound, user1pos[0], user1pos[1]);

      //Move the user dot
      if (xRound > (user1pos[0]+proximeter) || yRound > (user1pos[1]+proximeter) || xRound < (user1pos[0]-proximeter) || yRound < (user1pos[1]-proximeter)){
        timer = 0;
        user1pos[0] = xRound;
        user1pos[1] = yRound;
        user1pos[2] = zRound;
      }

      //User dot stood still
      if (xRound < (user1pos[0]+stopmove) && yRound < (user1pos[1]+stopmove) && zRound < (user1pos[2]+stopmove) && xRound > (user1pos[0]-stopmove) && yRound > (user1pos[1]-stopmove) && zRound > (user1pos[2]-stopmove) && xRound > 0 && yRound > 0 && zRound > 0){
        if (dot == 0){
          timer++;
          if (timer == timeLimit){
            if (trust<requiredTrust){
              trust = trust + 1;
            }
            else if (trust == requiredTrust){
              println("user 1 trusted");
              usertrusted[0] = 1;
              trust = 0;
              dot = 1;
              user1[0] = 0;
              user1[1] = 255;
              user1[2] = 0;
            }
            timer = 0;
          }
        }
      }

      if (usertrusted[0] == 0){
        //Turn on LED Movement
        //xAxsis
        if (user1pos[0] < LED[0]){
          mqtt.publish("Kinect", "LED0");
        }else if (user1pos[0] > LED[0] && user1pos[0] < LED[1]){
          mqtt.publish("Kinect", "LED1");
        }else if (user1pos[0] > LED[1] && user1pos[0] < LED[2]){
          mqtt.publish("Kinect", "LED2");
        }else if (user1pos[0] > LED[2] && user1pos[0] < LED[3]){
          mqtt.publish("Kinect", "LED3");
        }else if (user1pos[0] > LED[3] && user1pos[0] < LED[4]){
          mqtt.publish("Kinect", "LED4");
        }else if (user1pos[0] > LED[4] && user1pos[0] < LED[5]){
          mqtt.publish("Kinect", "LED5");
        }else if (user1pos[0] > LED[5] && user1pos[0] < LED[6]){
          mqtt.publish("Kinect", "LED6");
        }else if (user1pos[0] > LED[6] && user1pos[0] < LED[7]){
          mqtt.publish("Kinect", "LED7");
        }else if (user1pos[0] > LED[7] && user1pos[0] < LED[8]){
          mqtt.publish("Kinect", "LED8");
        }else if (user1pos[0] > LED[8] && user1pos[0] < LED[9]){
          mqtt.publish("Kinect", "LED9");
        }else if (user1pos[0] > LED[9] && user1pos[0] < LED[10]){
          mqtt.publish("Kinect", "LED10");
        }else if (user1pos[0] > LED[10] && user1pos[0] < LED[11]){
          mqtt.publish("Kinect", "LED11");
        }else if (user1pos[0] > LED[11] && user1pos[0] < LED[12]){
          mqtt.publish("Kinect", "LED12");
        }else if (user1pos[0] > LED[12] && user1pos[0] < LED[13]){
          mqtt.publish("Kinect", "LED13");
        }else if (user1pos[0] > LED[13]){
          mqtt.publish("Kinect", "LED14");
        }
        //zAxsis
        if (user1pos[2] < zAxsis[0]){
          mqtt.publish("Kinect", "zAxsis0");
        }else if (user1pos[2] >zAxsis[0] && user1pos[2] < zAxsis[1]){
          mqtt.publish("Kinect", "zAxsis1");
        }else if (user1pos[2] > zAxsis[1] && user1pos[2] < zAxsis[2]){
          mqtt.publish("Kinect", "zAxsis2");
        }else if (user1pos[2] > zAxsis[2] && user1pos[2] < zAxsis[3]){
          mqtt.publish("Kinect", "zAxsis3");
        }else if (user1pos[2] > zAxsis[3] && user1pos[2] < zAxsis[4]){
          mqtt.publish("Kinect", "zAxsis4");
        }else if (user1pos[2] > zAxsis[4] && user1pos[2] < zAxsis[5]){
          mqtt.publish("Kinect", "zAxsis5");
        }else if (user1pos[2] > zAxsis[5] && user1pos[2] < zAxsis[6]){
          mqtt.publish("Kinect", "zAxsis6");
        }else if (user1pos[2] > zAxsis[6] && user1pos[2] < zAxsis[7]){
          mqtt.publish("Kinect", "zAxsis7");
        }else if (user1pos[2] > zAxsis[7] && user1pos[2] < zAxsis[8]){
          mqtt.publish("Kinect", "zAxsis8");
        }else if (user1pos[2] > zAxsis[8] && user1pos[2] < zAxsis[9]){
          mqtt.publish("Kinect", "zAxsis9");
        }else if (user1pos[2] > zAxsis[9] && user1pos[2] < zAxsis[10]){
          mqtt.publish("Kinect", "zAxsis10");
        }else if (user1pos[2] > zAxsis[10] && user1pos[2] < zAxsis[11]){
          mqtt.publish("Kinect", "zAxsis11");
        }else if (user1pos[2] > zAxsis[11] && user1pos[2] < zAxsis[12]){
          mqtt.publish("Kinect", "zAxsis12");
        }else if (user1pos[2] > zAxsis[12] && user1pos[2] < zAxsis[13]){
          mqtt.publish("Kinect", "zAxsis13");
        }else if (user1pos[2] > zAxsis[13]){
          mqtt.publish("Kinect", "zAxsis14");
        }
      }
      else if (usertrusted[0] == 1){
        mqtt.publish("Kinect", "UserTrusted");
      }
    }
  }
}

void trackUser(int userZ, int userX, int userY){
  noStroke();
  smooth();
  ellipse(userX, userY, (userZ/5), (userZ/5));
}

void onNewUser(int userId){
  println("new user");
}

void onLostUser(int userId){
  println("user lost");
  timer = 0;
  if (userId == 1){
    user1[0] = 235; 
    user1[1] = 137; 
    user1[2] = 62; 
    usertrusted[0] = 0;
    trust = 0;
    dot = 0;
    mqtt.publish("Kinect", "Alert");
  }
}

