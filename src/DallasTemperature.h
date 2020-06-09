/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

class DallasTemperature {
    byte* rom;
    OneWire* oneWire;

  public:
    bool online;
    float value;
    DallasTemperature(byte* aRom, OneWire* aOneWire) : rom(aRom), oneWire(aOneWire), online(false) {}

    // вычитаем значения датчика
    // если возращается true, то чтение удалось
    bool read() {
      if (rom[0]) { // если датчик уже найден
        if (oneWire->reset() == 0)
          return false;
        oneWire->select(rom);
        oneWire->write(0xBE);
        byte ram[9];
        for (byte k = 0; k < 9; k++) {
          ram[k] = oneWire->read();
        }
        if (OneWire::crc8(ram, 8) == ram[8]) { // если crc верно
          online = true;
          int divider = 0;
          if (rom[0] == 0x10) // если это 18S20
            divider = 2;
          else if (rom[0] == 0x28) // если это 18B20
            divider = 16;
          float temp = (__int16)((ram[1] << 8) | ram[0]);
          value = temp / divider;
        }
        else
          online = false;

        return online;
      }
      return false;
    }

    // если вернётся true, то новый датчик найден и привязан
    bool search(byte aRomArr[][8], int aMax) {
      if (rom[0])
        return false; // уже привязан

      byte newRom[8];
      while (1) {
        if (oneWire->search(newRom)) {
          if (OneWire::crc8(newRom, 7) != newRom[7])
            return false;
          bool original = true;
          for (int i = 0; i < aMax; i++) {
            if (memcmp(aRomArr[i], newRom, 8) == 0) {
              original = false;
              break;
            }
          }
          if (original) {
            memcpy(rom, newRom, 8);
            return true;
          }
        }
        else
          return false;
      }
    }

    // запуск процесс измерения, вычитывать можно через 750 мс
    /*void convert() {
        oneWire->reset();
        oneWire->select(rom);
        //oneWire->write(0x44, 1);
        oneWire->write(0x44);
    }*/

    static bool convertAll(OneWire* aOneWire) {
        if (aOneWire->reset() == 0)
          return false;
        aOneWire->skip();
        //aOneWire->write(0x44, 1);
        aOneWire->write(0x44);
        return true;
    }

};
