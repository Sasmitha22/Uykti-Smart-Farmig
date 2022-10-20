/* This code works with GY-31 TCS3200 TCS230 color sensor module
 * It select a photodiode set and read its value (Red Set/Blue set/Green set) and displays it on the Serial monitor
 * Refer to www.surtrtech.com for more details
 */

#define s0 8       //Module pins wiring
#define s1 9
#define s2 10
#define s3 11
#define out 12

int data=0;        //This is where we're going to stock our values

void setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
   
}

void loop()                  //Every 2s we select a photodiodes set and read its data
{

   digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red value= "); 
   GetData();                   //Executing GetData function to get the value

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue value= ");
   GetData();

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green value= ");
   GetData();

   Serial.println();

   delay(2000);
}

void GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
}
