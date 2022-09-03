#line 1 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"

#define ENABLE_OTA  //if OTA need
//#define SENSOR_TYPE_DALLAS 
//#define SEND_DATA_TO_THINGSPEAK  //To send data please specify your api_key to Thingspeak
#define USE_IR_CONTR  1
#define USE_DHT11 1
//#define DHT12

const char* ssid     = "Zehn_YIT";
const char* password = "YYDS1024512";

#include <Arduino.h>


#ifdef ESP32
#include <SPIFFS.h>
#endif
#ifdef ESP8266
#include <ESP8266WiFi.h>

#include <ESP8266mDNS.h>
#include "coredecls.h"
#endif

#if USE_IR_CONTR 
#include <IRremoteESP8266.h>
#include <IRsend.h>


const uint16_t kIrLed = 5;
IRsend irsend(kIrLed);   

#define IR_MODLE_PIN 14

#define IR_CODE_0 0
#define IR_CODE_1 1
#define IR_CODE_HEAD    2
#define IR_CODE_LINK    3
#define IR_CODE_BLANK   4
uint8_t AC_CRT_VAL = 0xFF;
const uint16_t basecode[][2]={ {650, 550},
                               {650, 1650}, 
                               {9000, 4500},
                               {650, 20000},
                               {650, 40000}};
                                                                                //温度  风速
const uint64_t IR_ECODE[3][4]={
                               {0x442802052, 0x20009, 0x442802072, 0x1000916},  //关
                               {0x4c2802052, 0x20008, 0x4c2802072, 0x1000917}, //26   静音
                               {0x4c2802052, 0x20008, 0x4c2802072, 0x916}     //26  1
                            };
#include <assert.h>
#include <IRrecv.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>

const uint8_t kTimeout = 50;
const uint16_t kRecvPin = 2;                              
const uint16_t kCaptureBufferSize = 1024;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;  // kTolerance is normally 25%

// Legacy (No longer supported!)
//
// Change to `true` if you miss/need the old "Raw Timing[]" display.
#define LEGACY_TIMING_INFO false
// ==================== end of TUNEABLE PARAMETERS ====================

// Use turn on the save buffer feature for more complete capture coverage.
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

#endif


#if USE_DHT11 
  #include <DHT.h>
  #include <DHT_U.h>
  
  #define DHTPIN 2     // Digital pin connected to the DHT sensor 
  #define DHTTYPE    DHT11     // DHT 11
  DHT_Unified dht(DHTPIN, DHT11);
#endif

//Webserver

#ifdef ESP8266
#include <ESP8266WebServer.h>
 ESP8266WebServer server(80);

#endif

#if defined(ESP32) && defined(ENABLE_OTA)
#include <Update.h>
#endif

#include "spiffs_webserver.h"
bool isWebserver_started=false;




const int identity_led=2;

#ifdef SEND_DATA_TO_THINGSPEAK
//validate compiltion for issue #14
#include "HTTPSimpleClient.h"
#endif
///HTTPSimpleClient http;
extern "C"{
#include "homeintegration.h"
}
#ifdef ESP8266
#include "homekitintegrationcpp.h"
#endif


String pair_file_name="/pair.dat";

homekit_service_t* thermostat=NULL;
homekit_service_t* fan=NULL;



#define SENSOR_READ_PERIOD_MS 5000
#define SEND_THINGSPEAK_PERIOD_MS 500000

struct device_data_t{
  float temp=20.0;
  float hum=50.0;
  float pressure=1000.0;
  unsigned long next_read_sensor_ms=0;
  unsigned long next_send_thingspeak_ms=0;
};

device_data_t DeviceData;

#if USE_IR_CONTR 
#line 140 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void _senddata(uint64_t data, uint8 len);
#line 158 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void sendFramt(uint64_t data1, uint64_t data2, uint8_t framt);
#line 167 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void IRRevcCheck(void);
#line 242 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void setup();
#line 356 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void handleGetVal();
#line 365 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void handleSetVal();
#line 377 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void loop();
#line 416 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void init_hap_storage();
#line 436 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void storage_changed(char * szstorage,int bufsize);
#line 451 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void notify_hap();
#line 462 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void hap_update(homekit_characteristic_t *ch, homekit_value_t value, void *context);
#line 529 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void heaterOn();
#line 534 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void heaterOff();
#line 539 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void coolerOn();
#line 544 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void coolerOff();
#line 549 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void fan_alarm(void *arg);
#line 553 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void fanOn(uint16_t delay);
#line 558 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void fanOff();
#line 561 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
void readSensor();
#line 140 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
    void _senddata(uint64_t data, uint8 len)
    {
    
      for(int i = len - 1; i >= 0; i--)
      {
         // Serial.printf("aaa %d " ,i);
        if((data >> i ) & 1)
        {
            irsend.sendRaw(basecode[IR_CODE_1], 2, 38);
        }
        else
        {
            irsend.sendRaw(basecode[IR_CODE_0], 2, 38);
        }
      }

    }

    void sendFramt(uint64_t data1,  uint64_t data2, uint8_t framt)
    {
      irsend.sendRaw(basecode[IR_CODE_HEAD], 2, 38);
      _senddata(data1, 35);
      irsend.sendRaw(basecode[IR_CODE_LINK], 2, 38);
      _senddata(data2, 32);
      irsend.sendRaw(basecode[IR_CODE_BLANK], 2, 38);
    }

    void IRRevcCheck(void)
    {
      if (irrecv.decode(&results)) {
        // Display a crude timestamp.
        uint32_t now = millis();
        Serial.printf(D_STR_TIMESTAMP " : %06u.%03u\n", now / 1000, now % 1000);
        // Check if we got an IR message that was to big for our capture buffer.
        if (results.overflow)
          Serial.printf(D_WARN_BUFFERFULL "\n", kCaptureBufferSize);
        // Display the library version the message was captured with.
        Serial.println(D_STR_LIBRARY "   : v" _IRREMOTEESP8266_VERSION_STR "\n");
        // Display the tolerance percentage if it has been change from the default.
        if (kTolerancePercentage != kTolerance)
          Serial.printf(D_STR_TOLERANCE " : %d%%\n", kTolerancePercentage);
        // Display the basic output of what we found.
        Serial.print(resultToHumanReadableBasic(&results));
        // Display any extra A/C info if we have it.
        String description = IRAcUtils::resultAcToString(&results);
        if (description.length()) Serial.println(D_STR_MESGDESC ": " + description);
        yield();  // Feed the WDT as the text output can take a while to print.
    #if LEGACY_TIMING_INFO
        // Output legacy RAW timing info of the result.
        Serial.println(resultToTimingInfo(&results));
        yield();  // Feed the WDT (again)
    #endif  // LEGACY_TIMING_INFO
        // Output the results as source code
        Serial.println(resultToSourceCode(&results));
        Serial.println();    // Blank line between entries
        uint16_t i = 0;
        uint32_t raw_data  = 0;
        Serial.printf("anly: \n");
        uint64_t *rawhex = nullptr;
        uint32_t rawhex_32[2]={0,0};
        rawhex = (uint64_t *)&rawhex_32[0];
        while (i <= results.rawlen)
        {
          raw_data = results.rawbuf[i]*2 ;

          if (raw_data >= 520 && raw_data <= 780 )
          {
            i++;
            raw_data = results.rawbuf[i] * 2;
            if (raw_data >= 1400 && raw_data<= 1750)
            {
                Serial.print(" 1");  
                *rawhex = (*rawhex <<1 ) | 1;
            }
            else if(raw_data >= 450 && raw_data <=650)
            {
                Serial.print(" 0");  
                *rawhex = (*rawhex << 1 );
            }
            else
            {
                Serial.printf(" hex:%x%x d:%d " , rawhex_32[1], rawhex_32[0], raw_data);  
                rawhex_32[0] = 0;
                rawhex_32[1] = 0;
            }

          }
          else
          {
                Serial.printf(" aad:%d " , raw_data);  
                rawhex_32[0] = 0;
                rawhex_32[1] = 0;
          }
          i++;
        }
        Serial.printf("end: \n");

        yield();             // Feed the WDT (again)
      }
    }
#endif

void setup() {
 #ifdef ESP8266 
  disable_extra4k_at_link_time();
 #endif 
  Serial.begin(115200);
    delay(10);

  #if USE_IR_CONTR
    pinMode(IR_MODLE_PIN, INPUT_PULLUP);
    irsend.begin();
    delay(200);
    
    // Perform a low level sanity checks that the compiler performs bit field
    // packing as we expect and Endianness is as we expect.
    assert(irutils::lowLevelSanityCheck() == 0);

    Serial.printf("\n" D_STR_IRRECVDUMP_STARTUP "\n", kRecvPin);
    #if DECODE_HASH
      // Ignore messages with less than minimum on or off pulses.
      irrecv.setUnknownThreshold(kMinUnknownSize);
    #endif  // DECODE_HASH
    irrecv.setTolerance(kTolerancePercentage);  // Override the default tolerance.
    irrecv.enableIRIn();  // Start the receiver
    
  #endif
    // We start by connecting to a WiFi network
#ifdef ESP32
     if (!SPIFFS.begin(true)) {
      // Serial.print("SPIFFS Mount failed");
     }
#endif
#ifdef ESP8266
     if (!SPIFFS.begin()) {
      Serial.print("SPIFFS Mount failed");
     }
#endif


    Serial.println(ssid);
#ifdef ESP8266
  WiFi.mode(WIFI_STA);
    WiFi.begin((char*)ssid, (char*)password);
#else
    WiFi.begin(ssid, password);
#endif
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
   // Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

#ifdef SENSOR_TYPE_DHT
DHT.begin();
#endif
#ifdef SENSOR_TYPE_BME280
 if(!BME.begin(BME_ADDR))
   Serial.print("Failed to Init BME280: ");
#endif

#ifdef SENSOR_TYPE_DALLAS

#endif
/// now will setup homekit device

    //this is for custom storaage usage
    // In given example we are using \pair.dat   file in our spiffs system
    //see implementation below
    Serial.print("Free heap: ");
    Serial.println(system_get_free_heap_size());

  
    init_hap_storage();
  
    set_callback_storage_change(storage_changed);

    /// We will use for this example only one accessory (possible to use a several on the same esp)
    //Our accessory type is light bulb , apple interface will proper show that
    hap_setbase_accessorytype(homekit_accessory_category_air_conditioner);
    /// init base properties
    hap_initbase_accessory_service("ES","Yurik72","0","EspHapLed","1.0");
 
    
    // for base accessory registering temperature
    thermostat = hap_add_thermostat_service("Thermostat",hap_update,0);
    
    fan = hap_add_fan_service("Fan",hap_update,0);
   
   
   
hap_init_homekit_server();
String strIp=String(WiFi.localIP()[0]) + String(".") + String(WiFi.localIP()[1]) + String(".") +  String(WiFi.localIP()[2]) + String(".") +  String(WiFi.localIP()[3]); 
 //setup web server
#ifdef ESP8266      
   if(hap_homekit_is_paired()){
#endif
     delay(500);
      Serial.println("Setting web server");      
      SETUP_FILEHANDLES
      server.on("/get", handleGetVal);
      server.on("/set", handleSetVal);   
     server.begin(); 
     Serial.println(String("Web site http://")+strIp);  
     Serial.println(String("File system http://")+strIp+String("/browse")); 
      Serial.println(String("Update http://")+strIp+String("/update"));     
     isWebserver_started=true;
#ifdef ESP8266     
  }else{
      Serial.println("Web server is NOT SET, waiting for pairing");
  }
#endif   
}
void handleGetVal(){
  if(server.arg("var") == "temp")
    server.send(200, FPSTR(TEXT_PLAIN),String(DeviceData.temp));
  else if(server.arg("var") == "hum")
     server.send(200, FPSTR(TEXT_PLAIN),String(DeviceData.hum));
  else
    server.send(505, FPSTR(TEXT_PLAIN),"Bad args");  
     
}
void handleSetVal(){
  if (server.args() !=2){
    server.send(505, FPSTR(TEXT_PLAIN), "Bad args");
    return;
  }
  //to do analyze
  if(server.arg("var") == "ch1"){
  }


     
}
void loop() {
 if(DeviceData.next_read_sensor_ms<=millis()){
    readSensor();
    notify_hap();
    DeviceData.next_read_sensor_ms=millis()+SENSOR_READ_PERIOD_MS;
 }

#ifdef SEND_DATA_TO_THINGSPEAK
if(DeviceData.next_send_thingspeak_ms<=millis()){
    sendToThingspeak();
    
    DeviceData.next_send_thingspeak_ms=millis()+SEND_THINGSPEAK_PERIOD_MS;
 }
#endif
 
  #if USE_IR_CONTR
  if(digitalRead(IR_MODLE_PIN) == 0)
  {
    IRRevcCheck();
  }
  else
  { 
    if(AC_CRT_VAL != 0xff)
    {
      sendFramt(IR_ECODE[AC_CRT_VAL][0], IR_ECODE[AC_CRT_VAL][1], 1);
      sendFramt(IR_ECODE[AC_CRT_VAL][2], IR_ECODE[AC_CRT_VAL][3], 2);
      AC_CRT_VAL = 0xff;
    }
  }
  #endif

#ifdef ESP8266
  hap_homekit_loop();
#endif
 if(isWebserver_started)
    server.handleClient();

}

void init_hap_storage(){
  Serial.print("init_hap_storage");
 
    
  File fsDAT=SPIFFS.open(pair_file_name, "r");
 if(!fsDAT){
   Serial.println("Failed to read pair.dat");
   return;
 }
  int size=hap_get_storage_size_ex();
  char* buf=new char[size];
  memset(buf,0xff,size);
 int readed=fsDAT.readBytes(buf,size);
 // Serial.print("Readed bytes ->");
//  Serial.println(readed);
  hap_init_storage_ex(buf,size);
  fsDAT.close();
  delete []buf;

}
void storage_changed(char * szstorage,int bufsize){



  SPIFFS.remove(pair_file_name);
  File fsDAT=SPIFFS.open(pair_file_name, "w+");
  if(!fsDAT){
    Serial.println("Failed to open pair.dat");
    return;
  }
  fsDAT.write((uint8_t*)szstorage, bufsize);

  fsDAT.close();
}

void notify_hap(){

 if(thermostat){
  homekit_characteristic_t * ch_temp= homekit_service_characteristic_by_type(thermostat, HOMEKIT_CHARACTERISTIC_CURRENT_TEMPERATURE);
  if(ch_temp && !isnan(DeviceData.temp) &&  ch_temp->value.float_value!=DeviceData.temp ){
    ch_temp->value.float_value=DeviceData.temp;
    homekit_characteristic_notify(ch_temp,ch_temp->value);
  }
 }

}
void hap_update(homekit_characteristic_t *ch, homekit_value_t value, void *context) {
    Serial.println("hap_update dddd");
    if(!thermostat){
       Serial.println("service not defined");
      return;
   
    }
     homekit_characteristic_t * ch_temp= homekit_service_characteristic_by_type(thermostat, HOMEKIT_CHARACTERISTIC_CURRENT_TEMPERATURE);
     homekit_characteristic_t * ch_targetstate= homekit_service_characteristic_by_type(thermostat, HOMEKIT_CHARACTERISTIC_TARGET_HEATING_COOLING_STATE);
     homekit_characteristic_t * ch_currentstate= homekit_service_characteristic_by_type(thermostat, HOMEKIT_CHARACTERISTIC_CURRENT_HEATING_COOLING_STATE);

     homekit_characteristic_t*  ch_target_temperature=homekit_service_characteristic_by_type(thermostat, HOMEKIT_CHARACTERISTIC_TARGET_TEMPERATURE);
     homekit_characteristic_t* ch_heating_threshold=homekit_service_characteristic_by_type(thermostat, HOMEKIT_CHARACTERISTIC_HEATING_THRESHOLD_TEMPERATURE);
     homekit_characteristic_t* ch_cooling_threshold=homekit_service_characteristic_by_type(thermostat, HOMEKIT_CHARACTERISTIC_COOLING_THRESHOLD_TEMPERATURE);

     
if(!ch_temp || !ch_targetstate || !ch_target_temperature){
    Serial.println("characteristic wrong defined");
  return;
}

uint8_t state = ch_targetstate->value.int_value;
if(state== HOMEKIT_TARGET_HEATING_COOLING_STATE_OFF || state  == HOMEKIT_TARGET_HEATING_COOLING_STATE_COOL)
{
   Serial.printf("set AC to %d \n", state);
   AC_CRT_VAL = state;
}
else
{
    ch_targetstate->value.int_value = AC_CRT_VAL;
    homekit_characteristic_notify(ch_targetstate,ch_targetstate->value);
}
 DeviceData.temp = ch_target_temperature->value.float_value;
 
     if ((state == 1 && ch_temp->value.float_value < ch_target_temperature->value.float_value) ||
            (state == 3 && ch_temp->value.float_value < ch_heating_threshold->value.float_value)) {
        if (ch_currentstate->value.int_value != 1) {
            ch_currentstate->value = HOMEKIT_UINT8_VALUE(1);
            homekit_characteristic_notify(ch_currentstate, ch_currentstate->value);
            //heaterOn();
            //coolerOff();
            //fanOff();
            //fanOn(5000);
        }
    } else if ((state == 2 && ch_temp->value.float_value > ch_target_temperature->value.float_value) ||
            (state == 3 && ch_temp->value.float_value > ch_cooling_threshold->value.float_value)) {
        if (ch_currentstate->value.int_value != 2) {
            ch_currentstate->value = HOMEKIT_UINT8_VALUE(2);
            homekit_characteristic_notify(ch_currentstate, ch_currentstate->value);

            //coolerOn();
            //heaterOff();
            //fanOff();
            //fanOn(5000);
        }
    } else {
        if (ch_currentstate->value.int_value != 0) {
            ch_currentstate->value = HOMEKIT_UINT8_VALUE(0);
            homekit_characteristic_notify(ch_currentstate, ch_currentstate->value);

            //coolerOff();
            //heaterOff();
            //fanOff();
        }
    }
}

void heaterOn() {
   Serial.println("heaterOn");
}


void heaterOff() {
     Serial.println("heaterOff");
}


void coolerOn() {
    Serial.println("coolerOn");
}


void coolerOff() {
    Serial.println("coolerOff");
}


void fan_alarm(void *arg) {
     Serial.println("fan_alarm");
}

void fanOn(uint16_t delay) {
Serial.println("fanOn");
}


void fanOff() {
Serial.println("fanOff");
}
void readSensor(){

#ifdef SENSOR_TYPE_DHT
  DeviceData.temp= DHT.readTemperature();
  DeviceData.hum = DHT.readHumidity();
#endif
#ifdef  SENSOR_TYPE_BME280
 DeviceData.temp=BME.readTemperature();
 DeviceData.hum=BME.readHumidity();
 DeviceData.pressure=BME.readPressure();
#endif 
#ifdef SENSOR_TYPE_DALLAS
DALLAS.requestTemperatures(); // Send the command to get temperatures

  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  DeviceData.temp = DALLAS.getTempCByIndex(0);
#endif
  Serial.println(String("Temp")+String(DeviceData.temp)+String("  Hum:")+String(DeviceData.hum));
  #if 0
  if(isnan(DeviceData.temp)){
    Serial.println("Set default temp 20");
    DeviceData.temp=20.0;
  }
    if(isnan(DeviceData.hum)){
      Serial.println("Set default hum 50");
     DeviceData.hum=50.0;
  }
   if(isnan(DeviceData.pressure)){
    Serial.println("Set default pressure 1000");
    DeviceData.pressure=1000.0;
  }
  #endif
  
}


#ifdef SEND_DATA_TO_THINGSPEAK
const char* thing_api_key="YOUR KEY";
void sendToThingspeak_old(){
   Serial.println("sendToThingspeak start");
    String url="http://api.thingspeak.com";
    url=" https://api.thingspeak.com/update?api_key="+String(thing_api_key);
    HTTPSimpleClient http;
  
    
     url+="&field1="+String(DeviceData.temp);
     url+="&field2="+String(DeviceData.hum);
     url+="&field3="+String(DeviceData.pressure);
     Serial.println(url);
     //nt httpcode=http.POST(poststr);
     if(!http.begin(url)){
       Serial.println("Failed to connect to"+url );
    }
    int httpCode = http.GET();
   Serial.println("http code returns"+String(httpCode) );
    Serial.println("http returns"+http.getString() );
     
}
void sendToThingspeak(){
   Serial.println("sendToThingspeak start");
    String url="https://www.borneland.com/sensor/post/";
    
    HTTPSimpleClient http;
     String apiKeyValue="tPmAT5Ab3j7F9";
     String sensorName="14661474";
     String postString="api_key="+String(apiKeyValue);
     postString+="&chip_id="+String(sensorName);
     postString+="&temp="+String(DeviceData.temp);
     postString+="&hum="+String(DeviceData.hum);
     Serial.println(url);
     
     if(!http.begin(url)){
       Serial.println("Failed to connect to "+url );
    }
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  
    int httpcode = http.POST(postString);
    String response=http.getString();
    Serial.println("postString "+String(postString) );
   Serial.println("http code returns "+String(httpcode) );
   Serial.println("http code response "+String(response) );   
}
#endif

