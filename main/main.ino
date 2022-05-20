// bigger leg is anode 

void setup()
{
pinMode(4, OUTPUT); // Set GPIO22 as digital output pin
//pinMode(5, OUTPUT);
}

void loop() 
{
digitalWrite(4, HIGH); // Set GPIO22 active high
//digitalWrite(5, HIGH); // Set GPIO22 active high

delay(1000);  // delay of one second
digitalWrite(4, LOW); // Set GPIO22 active low
//digitalWrite(5, LOW); // Set GPIO22 active low

delay(1000); // delay of one second
}
