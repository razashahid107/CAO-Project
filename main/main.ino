void setup()
{
pinMode(32, OUTPUT); // Set GPIO22 as digital output pin
}

void loop() 
{
digitalWrite(32, HIGH); // Set GPIO22 active high
delay(1000);  // delay of one second
digitalWrite(32, LOW); // Set GPIO22 active low
delay(1000); // delay of one second
}