#ifndef PROJE1_H
#define PROJE1_H

// Ders yapısı
typedef struct
{
    char *dersAdi;
    unsigned short int kredi;
    unsigned short int puan;
} Ders;

// Öğrenci yapısı
typedef struct
{
    char *ogrAdi;
    char *ogrSoyAdi;
    char *bolumu;
    float ortalama;
    Ders *aldigiDersler;
} Ogrenci;

// Ders oluşturma fonksiyonu
Ders *dersOlustur(char *dersAdi, unsigned short int kredi, unsigned short int puan);
// Öğrenci oluşturma fonksiyonu
Ogrenci *ogrenciOlustur(char *ogrAdi, char *ogrSoyAdi, char *bolumu, float ortalama, Ders *aldigiDersler);
// Öğrenci bilgilerini yazdırma fonksiyonu
void ogrenciYazdir(Ogrenci *ogrenci);
// Öğrenci dizisini yazdırma fonksiyonu
void ogrenciDiziYazdir(Ogrenci *ogrenciler, int ogrenciSayisi);
// Belirli bir dersin ortalama puanını hesaplama fonksiyonu
float dersOrtalama(Ders *dersler, int dersSayisi, char *arananDersAdi);
// Belirli bir dersin standart sapmasını hesaplama fonksiyonu
float dersStandartSapma(Ders *dersler, int dersSayisi, char *arananDersAdi);
// Belirli iki ders arasındaki kovaryansı hesaplama fonksiyonu
float dersKovaryans(Ders *ders1, Ders *ders2, int dersSayisi);
// Belirli bir derste yüksek not alan öğrencileri listeleme fonksiyonu
void yuksekNotAlanlariListele(Ogrenci *ogrenciler, int ogrenciSayisi, char *arananDersAdi);
// Öğrenci bilgilerini dosyaya yazma fonksiyonu
void ogrenciDosyaYaz(Ogrenci *ogrenciler, int ogrenciSayisi, char *dosyaAdi);
// Dosyadan öğrenci bilgilerini okuma fonksiyonu
Ogrenci *dosyadanOgrenciOku(char *dosyaAdi, int *ogrenciSayisi);

#endif
