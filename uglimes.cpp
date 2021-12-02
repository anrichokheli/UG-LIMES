// UG-LIMES წარწერის გამომსახველი შუქდიოდების პინები
#define pin_U 2
#define pin_G 3
#define pin_ 4
#define pin_L 5
#define pin_I 6
#define pin_M 7
#define pin_E 8
#define pin_S 9

#define pin_PWM 10// შუქდიოდების მინუს(-) ფეხები

// ფუნქცია, რომელიც თანდათანობით აანთებს შუქდიოდ(ებ)ს მისთვის პარამეტრად გადაცემული დაყოვნებით მილიწამებში
void ledsOn(byte t) {
  for (int i = 255; i >= 0; i--) {
    analogWrite(pin_PWM, i);
    delay(t);
  }
}

// ფუნქცია, რომელიც თანდათანობით ჩააქრობს შუქდიოდ(ებ)ს მისთვის პარამეტრად გადაცემული დაყოვნებით მილიწამებში
void ledsOff(byte t) {
  for (int i = 0; i < 256; i++) {
    analogWrite(pin_PWM, i);
    delay(t);
  }
}

// ფუნქცია, რომელიც აანთებს/ჩააქრობს შუქდიოდებს პირველ პარამეტრში არსებული რიცხვის მქონე პინზე მიერთებული შუქდიოდიდან დაწყებული, მეორე პარამეტრის შესაბამისი შუქდიოდის ჩათვლით
// მე-3 პარამეტრი განსაზღვრავს ცვლილებებს შორის დაყოვნებას (სისწრაფეს)
// მე-4 პარამეტრი თუ არის ლოგიკური 1, მაშინ ნათების ინტენსივობა ნელა შეიცვლება, ხოლო თუ ლოგიკური 0 - მყისიერად
// მე-5 პარამეტრი განსაზღვრავს აინთოს თუ ჩაქრეს შუქდიოდი (ლოგიკური 0 - ჩაქრობა, ლოგიკური 1 - ანთება)
// მე-6 პარამეტრი თუ არის ლოგიკური 0, მაშინ მომდევნო შუქდიოდის ანთებამდე, წინა ჩაქრება
void ledsRange(byte firstPin, byte lastPin, int t, boolean soft, boolean state, boolean keepState)  {
  for (; firstPin <= lastPin; firstPin++) {
    digitalWrite(firstPin, state);
    if (soft)  {
      ledsOn(t);
      ledsOff(t);
    }
    else  {
      delay(t);
    }
    if (!keepState)
      digitalWrite(firstPin, 0);
  }
}

// ყველა შუქდიოდის აციმციმების ფუნქცია
void blinkAll(int t, byte q, boolean soft) {
  turnOnAllLED();
  for (byte n = 0; n < q; n++) {
    if (soft)  {
      ledsOn(t);
      ledsOff(t);
    }
    else  {
      digitalWrite(pin_PWM, !digitalRead(pin_PWM));
      delay(t);
      digitalWrite(pin_PWM, !digitalRead(pin_PWM));
    }
    delay(t);
  }
}

// ყველა შუქდიოდის ანთების ფუნქცია
void turnOnAllLED() {
  digitalWrite(pin_PWM, 0);
  ledsRange(pin_U, pin_S, 0, 0, 1, 1);
}

// ყველა შუქდიოდის და აგრეთვე PWM პინზე, ლოგიკური მდგომარეობის 0-ზე დაყენების ფუნქცია
void resetAll() {
  ledsRange(pin_U, pin_PWM, 0, 0, 0, 1);
}

void setup()  {
  // 2-10 პინების გამოცხადება როგორც გამოსავალი
  for (int i = pin_U; i <= pin_PWM; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  ledsRange(pin_L, pin_S, 5, 1, 1, 1);// რბილად აინთოს შუქდიოდები, რომლებიც გამოსახავს 'L'-ს, შემდეგ ჩაქრეს და იმავე შუქდიოდებთან ერთად, რბილად აინთოს მისი შემდეგიც.. ეს პროცესი მეორდება 'S'-ის ჩათვლით..
  ledsRange(pin_U, pin_, 5, 1, 1, 1);// ზემოხსენებული პრინციპით აინთოს 'U'-დან '-'-ს ჩათვლით..
  resetAll();// ყველა შუქდიოდის ჩაქრობა..
  // მეორდება წინა პროცესი, თუმცა მომდევნო შუქდიოდის ანთებამდე, წინა შუქდიოდი ანთებული რჩება და მომდევნო შუქდიოდები ინთება მყისიერად..
  ledsRange(pin_L, pin_S, 1000, 0, 1, 1);
  ledsRange(pin_U, pin_, 1000, 0, 1, 1);
  //
  resetAll();
  ledsRange(pin_U, pin_S, 1, 1, 1, 0);// ინთება ყველა შუქდიოდი რიგრიგობით.. მომდევნო შუქდიოდების ანთებამდე, წინა ქრება.. ანთება/ჩაქრობა ხდება თანდათანობით..
  resetAll();
  ledsRange(pin_U, pin_S, 500, 0, 1, 0);// ხდება წინა პროცესი, თუმცა ანთება/ჩაქრობა ხდება მყისიერად..
  resetAll();
  ledsRange(pin_U, pin_S, 500, 0, 1, 1);// ინთება ყველა შუქდიოდი მყისიერად, ჯერ პირველი, შემდეგ მეორე.. მომდევნო შუქდიოდების ანთების შემდეგაც, წინა შუქდიოდები ანთებული რჩება..
  resetAll();
  blinkAll(250, 10, 0);// ციმციმებს ყველა შუქდიოდი მყისიერად..
  resetAll();
  blinkAll(1, 10, 1);// ციმციმებს ყველა შუქდიოდი რბილად..
  turnOnAllLED();// ერთდროულად ინთება ყველა შუქდიოდი
  delay(10000);// პროგრამის მსვლელობის დაყოვნება 10000 მილიწამით (10 წამით)
  resetAll();
}