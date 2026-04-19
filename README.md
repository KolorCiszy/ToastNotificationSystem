This is a sample of Toast Notification System made in UE 5.6 with C++, Blueprints and UMG. 

The system implements following notifications:
<img width="576" height="956" alt="image" src="AdditionalAssets/toastDemo.gif" />

Regarding technical stuff:
- Notification widgets are pooled
- It is possible to send a notification for every player on the server as well as only for the local player
- The backend manager component implements a queue system and decouples that logic from widgets

Multiplayer showcase video:
<video src="AdditionalAssets/ToastDemoMultiplayer.mkv" width="600" autoplay loop muted></video>
