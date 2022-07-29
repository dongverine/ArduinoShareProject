#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "와이파이아이디";  // your network SSID (name)
char password[] = "와이파이비번";  // your network password
static byte target_mac1[] = { 0x11, 0xCC, 0x6A, 0x8E, 0xDE, 0xB3 };//pc
static byte target_mac2[] = { 0x11, 0x11, 0x32, 0xD6, 0xB5, 0x8B };//nas

String MyIp = "";

WiFiUDP udp;  // class를 udp로 지정
WiFiServer server(80);

void wake_up(byte target_mac[])
{
  byte pre_packet[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  byte broadcast[] = {255, 255, 255, 255};
  
  udp.beginPacket(broadcast, 7);
  udp.write(pre_packet, 6);
  
  for(int i=0 ; i<16 ; i++)
  {
    udp.write(target_mac, 6);
  }
  udp.endPacket();
}

void wifiSetup(){
  char str1[100];
    
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  MyIp = "http://"+String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(WiFi.localIP()[3])+"          ";
  Serial.println(MyIp);
  Serial.println(".");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");  
  delay(500);
}

/*
	아두이노가 실행되면 딱한번 실한한다. 
*/
void setup() {
  Serial.begin(115200);
  
  delay(10);
  
  wifiSetup();
}

/*
	아두이노가 실행되는동안 계속 실행된다.
*/
void loop() {
  delay(200);
  if (WiFi.status() != WL_CONNECTED){
    wifiSetup(); 
  }
  
  WiFiClient client = server.available();
  if(client){  
    Serial.println("new client");    
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
  
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>WOL</title>");
    client.println("<meta name='viewport' content='width=200px, user-scalable=no'>");
    client.println("<link href='data:image/x-icon;base64,AAABAAEAEBAAAAAAAABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8AJCQk/yQkJP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/0ZGRv8XFxf/////AP///wD///8A////AP///////////////+7u7v9OTk7/sbGx/11dXf9KSkr///////////+lpaX/4eHh/////wD///8A////AAAAAP8AAAD///////////+8vLz///////X19f/t7e3/gICA/5eXl////////////wAAAP8AAAD/////AKysrP8AAAD/AAAA/wAAAP+enp7/////////////////////////////////5OTk/wAAAP8AAAD/AAAA/6ysrP////8A////AP///wCurq6PlJSUzP///wD///8A////AP///wD///8A////AJSUlMyQkJDY////AP///wD///8A////AP///wD///8AAAAA/wAAAP////8A////AP///wD///8A////AP///wAAAAD/AAAA/////wD///8A////AP///wD///8AAAAA/wAAAP8AAAD/////AP///wD///8A////AP///wD///8AAAAA/wAAAP8AAAD/////AP///wD///8ACwsL/wAAAP8AAAD/lJSU2AAAAP8AAAD/cnJy/1hYWP8AAAD/AAAA/2FhYdgHBwf/AAAA/wAAAP////8A////AP///wD///8A////AP///wAAAAD/s7Oz/wAAAP8AAAD/x8fH/wAAAP////8A////AP///wD///8A////AP///wD///8A////AP///wAAAAD/AAAA/////wAAAAD/AAAA/////wAAAAD/AAAA/////wD///8A////AP///wD///8A////AP///wD///8AAAAA/wAAAP+qqqqlAAAA/wAAAP9lZWXjAAAA/wAAAP////8A////AP///wD///8A////AP///wD///8A////ALa2tv////8A9vb2UQAAAP8AAAD/////Uf///wDAwMD/////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wBcXFz/AAAA/////wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A////AP///wD///8A//8AAP//AADAAwAAwAMAAIABAAAAAAAA5+cAAOfnAADH4wAAgAEAAPgfAADyTwAA8A8AAPZvAAD+fwAA//8AAA==' rel='icon' type='image/x-icon' />");
    client.println("<style>");
    client.println("span{");
    client.println("}");
    client.println("a{");
    client.println("    text-decoration: none;");
    client.println("    width:100px;");
    client.println("    background-color: #FAEBD7;");
    client.println("}");
    client.println("a:link, a:visited {");
    client.println("    color: maroon;");
    client.println("    text-align: center;");
    client.println("    display: inline-block;");
    client.println("}");
    client.println("a:hover, a:active {");
    client.println("}");    
    client.println("</style>");
    client.println("<script>");  
    if (request.indexOf("/seq=0") != -1) {
      wake_up(target_mac1);      
      client.println("alert('send wol 1');history.back();");      
    } 
    if (request.indexOf("/seq=1") != -1){
      wake_up(target_mac2);
      client.println("alert('send wol 2');history.back();");  
    }
    client.println("</script>");  
    client.println("</head><body>");
    client.println("<span>WOL1</span> <a href=\"/seq=0\">My PC</a><br>");
    client.println("<span>WOL2</span> <a href=\"/seq=1\">My Nas</a><br>");
    client.println("</body>");  
    client.println("</html>");
   
    delay(10);
    client.stop();
    Serial.println("Client disconnected");
    Serial.println("");    
  }
}
