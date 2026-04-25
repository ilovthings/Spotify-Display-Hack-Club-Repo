[BOM v1.csv](https://github.com/user-attachments/files/27070534/BOM.v1.csv)<p align="center"><img width="360" height="363" alt="74249482-b3a2-498f-9167-37c33aae166d_removalai_preview" src="https://github.com/user-attachments/assets/5a9456b8-0707-4983-a9c3-2d1734ca4b7d" />

<h1>About this project</h1>
<hr>
<p> This is a hardware project that I'm doing for a "Hack club" event, more specifically Stasis. The current iteration is the third and possibly last version of the digital plan and part of my Spotify display project. I think I have been working on this project for about 3 and a half weeks, jajaja.
</p>

<h2> What does this do? </h2>
<hr>
<p> As its name says, it is a display for my Spotify listening. I use an ESP32 dev board; this is so I can use the internet and Bluetooth. One of the main features is also the input buttons, which affect directly the state of my current Spotify playback. The main buttons are</p>
-Pause / Play
-Volume
-Last Song
-Next Song

<h2>Bill Of Materials</h2>
<hr>
<p>
For this project I need some resources. As I mentioned before, I used an ESP32 dev board, three 6x6 push buttons, a TFT screen, and a potentiometer.

Here is the BOM:
[Uplo"Reference","Qty","Value","DNP","Exclude from BOM","Exclude from Board","Footprint","Datasheet"
"RV1","1","R_Potentiometer","","","","Potentiometer_THT:Potentiometer_Alps_RK09K_Single_Horizontal","https://media.digikey.com/pdf/Data%20Sheets/Alps%20Alphine/Alps%20RK09%20Potentiometer.pdf"
"SW1,SW2,SW3","3","SW_Push","","","","Button_Switch_THT:SW_PUSH_6mm_H4.3mm","https://www.hdk.co.jp/pdf/eng/e291702.pdf"
"U1","1","ESP32-C3-DevKitM-1","","","","RF_Module:ESP32-C3-DevKitM-1","https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/hw-reference/esp32c3/user-guide-devkitm-1.html"
"U2","1","CR2013-MI2120","","","","Display:CR2013-MI2120","http://pan.baidu.com/s/11Y990"
ading BOM v1.csv…]()
</p>
   
<h2>Here are some assets that i used:</h2>
<hr>

TFT Display: "[https://grabcad.com/library/tft-display-1-8-1](https://grabcad.com/library/tft-display-1-8-1)"

ESP32 Dev Board: "[https://grabcad.com/library/wemos-esp32-c3-mini-v1-0-0-1"](https://grabcad.com/library/esp-32s-development-board-1)"

6x6 buttons: "[https://grabcad.com/library/outemu-mx-switch-1](https://grabcad.com/library/push-button-smt-for-pcb-12x12-mm-1)"

<h2>I hope the code is rigth:</h2>
<hr>
It is in the "Essentials" folder.

<h2>Here is a picture of the model from the file and the wiring diagram:</h2>
<hr>
[Wiring Diagram.pdf](https://github.com/user-attachments/files/27070551/Wiring.Diagram.pdf)
