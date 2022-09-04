# 1 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"


//#define SENSOR_TYPE_DALLAS 
//#define SEND_DATA_TO_THINGSPEAK  //To send data please specify your api_key to Thingspeak


//#define DHT12

const char* ssid = "Zehn_YIT";
const char* password = "YYDS1024512";

# 13 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2






# 20 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2

# 22 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
# 23 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2



# 27 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
# 28 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2


const uint16_t kIrLed = 4;
IRsend irsend(kIrLed);
# 40 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
uint8_t AC_CRT_VAL = 0xFF;
const uint16_t basecode[][2]={ {650, 550},
                               {650, 1650},
                               {9000, 4500},
                               {650, 20000},
                               {650, 40000}};
                                                                                //温度  风速
const uint64_t IR_ECODE[3][4]={
                               {0x442802052, 0x20009, 0x442802072, 0x1000916}, //关
                               {0x4c2802052, 0x20008, 0x4c2802072, 0x1000917}, //26   静音
                               {0x4c2802052, 0x20008, 0x4c2802072, 0x916} //26  1
                            };
# 53 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
# 54 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
# 55 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
# 56 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
# 57 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2

const uint8_t kTimeout = 50;
const uint16_t kRecvPin = 2;
const uint16_t kCaptureBufferSize = 1024;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance; // kTolerance is normally 25%

// Legacy (No longer supported!)
//
// Change to `true` if you miss/need the old "Raw Timing[]" display.

// ==================== end of TUNEABLE PARAMETERS ====================

// Use turn on the save buffer feature for more complete capture coverage.
IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results; // Somewhere to store the results






# 80 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2



  DHT DHT(5 /* Digital pin connected to the DHT sensor */, DHT11);



//Webserver


# 91 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
 ESP8266WebServer server(80);







# 100 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
bool isWebserver_started=false;




//float min_value_t = 0, min_step_t=1, max_value_t = 6;
float *min_step_t = 
# 106 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3 4
                   __null
# 106 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
                       ;

const int identity_led=2;





///HTTPSimpleClient http;
extern "C"{
# 117 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2
}

# 120 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 2



String pair_file_name="/pair.dat";

homekit_service_t* thermostat=
# 125 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3 4
                             __null
# 125 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
                                 ;
homekit_service_t* fan=
# 126 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3 4
                      __null
# 126 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
                          ;
homekit_service_t* temperature=
# 127 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3 4
                              __null
# 127 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
                                  ;
homekit_service_t* humidity=
# 128 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3 4
                           __null
# 128 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
                               ;
homekit_service_t* DHT_SENSOR=
# 129 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3 4
                             __null
# 129 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
                                 ;





struct device_data_t{
  float ac_temp=26.0;
  float sensor_temp=26.0;
  float sensor_hum=50.0;
  float pressure=1000.0;
  unsigned long next_read_sensor_ms=0;
  unsigned long next_send_thingspeak_ms=0;
};

device_data_t DeviceData;


    void _senddata(uint64_t data, uint8 len)
    {

      for(int i = len - 1; i >= 0; i--)
      {
         // Serial.printf("aaa %d " ,i);
        if((data >> i ) & 1)
        {
            irsend.sendRaw(basecode[1], 2, 38);
        }
        else
        {
            irsend.sendRaw(basecode[0], 2, 38);
        }
      }

    }

    void sendFramt(uint64_t data1, uint64_t data2, uint8_t framt)
    {
      irsend.sendRaw(basecode[2], 2, 38);
      _senddata(data1, 35);
      irsend.sendRaw(basecode[3], 2, 38);
      _senddata(data2, 32);
      irsend.sendRaw(basecode[4], 2, 38);
    }

    void IRRevcCheck(void)
    {
      if (irrecv.decode(&results)) {
        // Display a crude timestamp.
        uint32_t now = millis();
        Serial.printf("Timestamp" " : %06u.%03u\n", now / 1000, now % 1000);
        // Check if we got an IR message that was to big for our capture buffer.
        if (results.overflow)
          Serial.printf("WARNING: IR code is too big for buffer (>= %d). " "This result shouldn't be trusted until this is resolved. " "Edit & increase `kCaptureBufferSize`." "\n", kCaptureBufferSize);
        // Display the library version the message was captured with.
        Serial.println("Library" "   : v" "_IRREMOTEESP8266_VERSION_MAJOR" "." "_IRREMOTEESP8266_VERSION_MINOR" "." "_IRREMOTEESP8266_VERSION_PATCH" "\n");
        // Display the tolerance percentage if it has been change from the default.
        if (kTolerancePercentage != kTolerance)
          Serial.printf("Tolerance" " : %d%%\n", kTolerancePercentage);
        // Display the basic output of what we found.
        Serial.print(resultToHumanReadableBasic(&results));
        // Display any extra A/C info if we have it.
        String description = IRAcUtils::resultAcToString(&results);
        if (description.length()) Serial.println("Mesg Desc." ": " + description);
        yield(); // Feed the WDT as the text output can take a while to print.





        // Output the results as source code
        Serial.println(resultToSourceCode(&results));
        Serial.println(); // Blank line between entries
        uint16_t i = 0;
        uint32_t raw_data = 0;
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

        yield(); // Feed the WDT (again)
      }
    }


void setup() {

  disable_extra4k_at_link_time();

  Serial.begin(115200);
    delay(10);

    pinMode(14, 0x02);

    pinMode(12, 0x02);
    irsend.begin();
    delay(200);

    // Perform a low level sanity checks that the compiler performs bit field
    // packing as we expect and Endianness is as we expect.
    
# 264 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3
   ((
# 264 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
   irutils::lowLevelSanityCheck() == 0
# 264 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3
   ) ? (void)0 : __assert_func ((__extension__({static const char __pstr__[] __attribute__((__aligned__(4))) __attribute__((section( "\".irom0.pstr." "EspHap_ThermostatControl.ino" "." "264" "." "168" "\", \"aSM\", @progbits, 1 #"))) = ("EspHap_ThermostatControl.ino"); &__pstr__[0];})), 264, __PRETTY_FUNCTION__, (__extension__({static const char __pstr__[] __attribute__((__aligned__(4))) __attribute__((section( "\".irom0.pstr." "EspHap_ThermostatControl.ino" "." "264" "." "169" "\", \"aSM\", @progbits, 1 #"))) = (
# 264 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
   "irutils::lowLevelSanityCheck() == 0"
# 264 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino" 3
   ); &__pstr__[0];}))))
# 264 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
                                              ;

    Serial.printf("\n" "IRrecvDump is now running and waiting for IR input on Pin %d" "\n", kRecvPin);

      // Ignore messages with less than minimum on or off pulses.
      irrecv.setUnknownThreshold(kMinUnknownSize);

    irrecv.setTolerance(kTolerancePercentage); // Override the default tolerance.
    irrecv.enableIRIn(); // Start the receiver


    // We start by connecting to a WiFi network






     if (!SPIFFS.begin()) {
      Serial.print("SPIFFS Mount failed");
     }



    Serial.println(ssid);

  WiFi.mode(WIFI_STA);
    WiFi.begin((char*)ssid, (char*)password);



    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
   // Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());


  DHT.begin();
# 316 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
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


    thermostat = hap_add_thermostat_service("Thermostat",hap_update,0);

    // for base accessory registering temperature
    //temperature = hap_add_temperature_service("Temperature");

    // Adding second accessory for humidity
    temperature = hap_add_temp_as_accessory(homekit_accessory_category_sensor, "Temperature");
    humidity = hap_add_hum_as_accessory(homekit_accessory_category_sensor, "Humidity");

    fan = hap_add_fan_service("Fan",hap_update,0);

    //String strIp=String(WiFi.localIP()[0]) + String(".") + String(WiFi.localIP()[1]) + String(".") +  String(WiFi.localIP()[2]) + String(".") +  String(WiFi.localIP()[3]); 

     homekit_characteristic_t * ch_targetstate= homekit_service_characteristic_by_type(thermostat, ("33"));

     homekit_characteristic_t* ch_target_temperature=homekit_service_characteristic_by_type(thermostat, ("35"));


      ch_targetstate->value.int_value = 2;
      homekit_characteristic_notify(ch_targetstate, ch_targetstate->value);

      ch_target_temperature->value.float_value = 26.0;
      homekit_characteristic_notify(ch_target_temperature, ch_target_temperature->value);
# 370 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
  hap_init_homekit_server();
 //setup web server

   if(hap_homekit_is_paired()){

     delay(500);
      Serial.println("Setting web server");
      //SETUP_FILEHANDLES
      //server.on("/get", handleGetVal);
      //server.on("/set", handleSetVal);   
     //server.begin(); 
     //Serial.println(String("Web site http://")+strIp);  
     //Serial.println(String("File system http://")+strIp+String("/browse")); 
     //Serial.println(String("Update http://")+strIp+String("/update"));     
     //isWebserver_started=true;

  }else{
      Serial.println("Web server is NOT SET, waiting for pairing");
  }

}
void handleGetVal(){

  Serial.println("handleGetVal\n");
  if(server.arg("var") == "temp")
    server.send(200, (reinterpret_cast<const __FlashStringHelper *>(TEXT_PLAIN)),String(DeviceData.sensor_temp));
  else if(server.arg("var") == "hum")
  {
     server.send(200, (reinterpret_cast<const __FlashStringHelper *>(TEXT_PLAIN)),String(DeviceData.sensor_hum));
  }
  else
    server.send(505, (reinterpret_cast<const __FlashStringHelper *>(TEXT_PLAIN)),"Bad args");

}
void handleSetVal(){
  if (server.args() !=2){
    server.send(505, (reinterpret_cast<const __FlashStringHelper *>(TEXT_PLAIN)), "Bad args");
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
    DeviceData.next_read_sensor_ms=millis()+5000;
 }
# 430 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
  if(digitalRead(12) == 0)
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



  hap_homekit_loop();

 if(isWebserver_started)
    server.handleClient();

}

void init_hap_storage(){
  Serial.print("init_hap_storage \n");

 if( digitalRead(14) == 0)//不写入配对码  就重新开始配对
 {
   Serial.println("reset to  pairring");
   return;
 }

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
void storage_changed(char * szstorage,int bufsize) //回调函数 ，会传配对码给homekit 服务
{
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
  homekit_characteristic_t * ch_temp1= homekit_service_characteristic_by_type(thermostat, ("11"));
  if(ch_temp1 && !isnan(DeviceData.ac_temp) && ch_temp1->value.float_value!=DeviceData.ac_temp ){
    ch_temp1->value.float_value=DeviceData.ac_temp;
    homekit_characteristic_notify(ch_temp1,ch_temp1->value);
  }
 }
 if(temperature){
  homekit_characteristic_t * ch_temp= homekit_service_characteristic_by_type(temperature, ("11"));
  if(ch_temp && !isnan(DeviceData.sensor_temp) && ch_temp->value.float_value!=DeviceData.sensor_temp ){
    ch_temp->value.float_value=DeviceData.sensor_temp;
    homekit_characteristic_notify(ch_temp,ch_temp->value);
  }
 }
if(humidity){
  homekit_characteristic_t * ch_hum= homekit_service_characteristic_by_type(humidity, ("10"));
  if(ch_hum && !isnan(DeviceData.sensor_hum) && ch_hum->value.float_value!=DeviceData.sensor_hum){
    ch_hum->value.float_value=DeviceData.sensor_hum;
    homekit_characteristic_notify(ch_hum,ch_hum->value);
  }
}

}
void hap_update(homekit_characteristic_t *ch, homekit_value_t value, void *context) {
    Serial.println("hap_update dddd");
    if(!thermostat){
       Serial.println("service not defined");
      return;

    }
     homekit_characteristic_t * ch_temp= homekit_service_characteristic_by_type(thermostat, ("11"));
     homekit_characteristic_t * ch_targetstate= homekit_service_characteristic_by_type(thermostat, ("33"));
     homekit_characteristic_t * ch_currentstate= homekit_service_characteristic_by_type(thermostat, ("F"));

     homekit_characteristic_t* ch_target_temperature=homekit_service_characteristic_by_type(thermostat, ("35"));
     homekit_characteristic_t* ch_heating_threshold=homekit_service_characteristic_by_type(thermostat, ("12"));
     homekit_characteristic_t* ch_cooling_threshold=homekit_service_characteristic_by_type(thermostat, ("D"));//制冷最低温度

//DeviceData.ac_temp =  ch_target_temperature->value.float_value > DeviceData.sensor_temp ? DeviceData.sensor_temp : ch_target_temperature->value.float_value; //22.9.4 暂时不支持制暖

if(!ch_temp || !ch_targetstate || !ch_target_temperature){
    Serial.println("characteristic wrong defined");
  return;
}



uint8_t state = ch_targetstate->value.int_value;

if(state== 0 || state == 2)
{
   Serial.printf("set AC to %d \n", state);
   AC_CRT_VAL = state;
}


   Serial.println(String("Temp")+String(ch_temp->value.float_value));

     if ((state == 1 && ch_temp->value.float_value < ch_target_temperature->value.float_value) ||
            (state == 3 && ch_temp->value.float_value < ch_heating_threshold->value.float_value))
    {
        if (ch_currentstate->value.int_value != 1) {
            ch_currentstate->value = HOMEKIT_UINT8_VALUE(1); //
            homekit_characteristic_notify(ch_currentstate, ch_currentstate->value);
            Serial.printf("HEAT     %d \n", ch_currentstate->value.int_value);
        }
    }
    else if ((state == 2 && ch_temp->value.float_value > ch_target_temperature->value.float_value) ||
            (state == 3 && ch_temp->value.float_value > ch_cooling_threshold->value.float_value))
    {
        if (ch_currentstate->value.int_value != 2) {
            ch_currentstate->value = HOMEKIT_UINT8_VALUE(2);
            homekit_characteristic_notify(ch_currentstate, ch_currentstate->value);
            Serial.printf("COOL     %d \n", ch_currentstate->value.int_value);
        }
    } else
    {
        if (ch_currentstate->value.int_value != 0)
        {
            ch_currentstate->value = HOMEKIT_UINT8_VALUE(0);
            homekit_characteristic_notify(ch_currentstate, ch_currentstate->value);
            Serial.printf("OFF     %d \n", ch_currentstate->value.int_value);
        }

    }

}

void readSensor(){


  DeviceData.sensor_temp= DHT.readTemperature();
  DeviceData.sensor_hum = DHT.readHumidity();
  DeviceData.ac_temp = DeviceData.sensor_temp ;
  Serial.println(String("Temp")+String(DeviceData.sensor_temp)+String("  Hum:")+String(DeviceData.sensor_hum));
  if(isnan(DeviceData.sensor_temp)){
    Serial.println("Set default temp 20");
    DeviceData.sensor_temp=26.0;
  }
    if(isnan(DeviceData.sensor_hum)){
      Serial.println("Set default hum 50");
     DeviceData.sensor_hum=50.0;
  }
# 610 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
  Serial.println(String("Temp")+String(DeviceData.sensor_temp)+String("  Hum:")+String(DeviceData.sensor_hum));
# 626 "d:\\DOCUMENT\\pro\\withing2.0\\arduino\\homeKit_AC\\EspHap_ThermostatControl.ino"
}
