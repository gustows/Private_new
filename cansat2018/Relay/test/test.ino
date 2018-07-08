enum state{ide , separated, landing , cut_rope , rdy }; 
String dcode_status(int rover)
{
// read state from lora to rover
  
  if( rover == ide)
  return "idle" ;
  if( rover == separated)
  return  "separated"; 
  if( rover == landing)
   return  "landing"; 
  if( rover == cut_rope)
   return  "cut rope"; 
  if( rover == rdy)
   return "ready";
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.println(dcode_status(2));
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
