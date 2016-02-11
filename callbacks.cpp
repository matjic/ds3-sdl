#include <iostream>
#include <curl/curl.h>
#include "callbacks.h"

using namespace std;

void postToKodi(string data);
int postJSON(string data, const char* path);
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
void Input(string key);
void Player(string key);
void Speed(string change);
void Volume(string change);

#ifndef LINUX
const char* KODI_START_COMMAND = "if ! pgrep \"Kodi\" >/dev/null; then nohup /Applications/Kodi.app/Contents/MacOS/Kodi >/dev/null  & fi";
#else
const char* KODI_START_COMMAND = "if ! pgrep \"kodi\" >/dev/null; then nohup kodi & fi";
#endif

void Home()
{
    //Start Kodi
    std::cout << "Starting Kodi..." << endl;
    system(KODI_START_COMMAND);
}

void InputDown()
{
    Input("Down");
}
void InputLeft()
{
    Input("Left");
}
void InputUp()
{
    Input("Up");
}
void InputRight()
{
    Input("Right");
}
void InputBack()
{
    Input("Back");
}
void InputSelect()
{
    Input("Select");
}
void InputHome()
{
    Input("Home");
}
void PlayPause()
{
    Player("PlayPause");
}
void Stop()
{
    Player("Stop");
}
void SlowDown()
{
    Speed("decrement");
}
void SpeedUp()
{
    Speed("increment");
}
void VolumeDown()
{
    Volume("decrement");
}
void VolumeUp()
{
    Volume("increment");
}

void Input(string key)
{
    postToKodi("{\"jsonrpc\":\"2.0\",\"method\":\"Input." + key + "\",\"id\":1}");
}
void Player(string key)
{
   postToKodi("{\"jsonrpc\":\"2.0\",\"method\":\"Player." + key + "\",\"id\":1,\"params\":{\"playerid\":1}}");
}
void Speed(string change)
{
    postToKodi("{\"jsonrpc\":\"2.0\",\"method\":\"Player.SetSpeed\",\"id\":1,\"params\":{\"playerid\":1,\"speed\":\"" + change + "\"}}");
}
void Volume(string change)
{
    postToKodi("{\"jsonrpc\":\"2.0\",\"method\":\"Application.SetVolume\",\"id\":1,\"params\":{\"volume\":\"" + change + "\"}}");
}

void postToKodi(string data)
{
    //fire and forget
    postJSON(data, "http://localhost:8080/jsonrpc");
}

//taken from cURL documentation
int postJSON(string data, const char* path)
{

  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    struct curl_slist *chunk = NULL;
 
    /* Remove a header curl would otherwise add by itself */ 
    chunk = curl_slist_append(chunk, "Content-Type: application/json");
 
    /* Add a custom header */ 
    chunk = curl_slist_append(chunk, "Accept: application/json");

    /* set our custom set of headers */ 
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);


    curl_easy_setopt(curl, CURLOPT_URL, path);

    /* Now specify the POST data */ 
    curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, data.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      //fprintf(stderr, "curl_easy_perform() failed: %s\n",
      //        curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return -1;
  }
  curl_global_cleanup();
  return 0;
}

//taken from cURL documentation
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
   return size * nmemb;
}