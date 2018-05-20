boolean no2;
boolean no2now;
boolean no3now;
int count;

//music
int speakerPin = 9;
// 依照簡譜的順序，填入代表的音符，空白代表休止符
char notes[] = "ggagCb ggagDC ggGECba FFECDC";
//char notes[] = "cdefg ab";
// 決定每個音階的拍子，注意這邊用 unsigned long 所以拍子只能是正整數
unsigned long beats[] = {1,1,2,2,2,2,2,1,1,2,2,2,2,2,1,1,2,2,2,2,2,1,1,1,2,2,2,2};
//unsigned long beats[] = {1,1,1,1,1,2,1,1};
// 利用 sizeof()，算出總共要多少音符
int length = sizeof(notes);
// 決定一拍多長，這邊一拍 300 ms
int tempo = 300;


// setup() 會先被執行且只會執行一次
void setup() {
  pinMode(6, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(2, INPUT);

  no2 = LOW;
  no2now = 0;
  no3now = 0;
  count = 0;
  digitalWrite(6, LOW);

}

// loop() 裡面的程式會不斷重複執行
void loop() {
  no2now = digitalRead(2);
  if (no2 == LOW && no2now == HIGH) {
    count += 1;
    digitalWrite(6, HIGH);
    showmusic();
  }
  no2 = no2now;

}
void showmusic()
{
  // 利用 for 來播放我們設定的歌曲，一個音一個音撥放
  for (int i = 0; i < length; i++) {
    
  // 如果是空白的話，不撥放音樂
    if (notes[i] == ' ') 
    {
      delay(beats[i] * tempo); // rest
    } 
    else 
    {
      // 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
      playNote(speakerPin,notes[i], beats[i] * tempo);
    }
    // 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
    delay(tempo/10);
  
  }
  }
  void playNote(int OutputPin, char note, unsigned long duration) 
{
  // 音符字元與對應的頻率由兩個矩陣表示
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C','D','E','F','G','A','B' };
  int tones[] = { 261, 294, 330, 349, 392, 440, 494, 523,587,659,698,784,880,988 };

  // 播放音符對應的頻率
  for (int i = 0; i < 14; i++) 
  {
    no3now = digitalRead(6);
    if (names[i] == note)
    {
      if (no3now == HIGH) 
      {
        digitalWrite(6, LOW);
      }
      else
      {
        digitalWrite(6, HIGH);
       }
      tone(OutputPin,tones[i], duration);
      //下方的 delay() 及 noTone ()，測試過後一定要有這兩行，整體的撥放出來的東西才不會亂掉，可能是因為 Arduino 送出tone () 頻率後會馬上接著執行下個指令，不會等聲音播完，導致撥出的聲音混合而亂掉
      delay(duration);
      noTone(OutputPin);
    }
  }
}
