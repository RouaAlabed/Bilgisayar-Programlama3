
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "proje1.h"

// Fonksiyonların implementasyonları burada yer alacak

// Ders oluşturma fonksiyonu
Ders *dersOlustur(char *dersAdi, unsigned short int kredi, unsigned short int puan)
{
    Ders *ders = (Ders *)malloc(sizeof(Ders));
    if (ders != NULL)
    {
        ders->dersAdi = strdup(dersAdi);
        ders->kredi = kredi;
        ders->puan = puan;
    }
    return ders;
}

// Öğrenci oluşturma fonksiyonu
Ogrenci *ogrenciOlustur(char *ogrAdi, char *ogrSoyAdi, char *bolumu, float ortalama, Ders *aldigiDersler)
{
    Ogrenci *ogrenci = (Ogrenci *)malloc(sizeof(Ogrenci));
    if (ogrenci != NULL)
    {
        ogrenci->ogrAdi = strdup(ogrAdi);
        ogrenci->ogrSoyAdi = strdup(ogrSoyAdi);
        ogrenci->bolumu = strdup(bolumu);
        ogrenci->ortalama = ortalama;
        ogrenci->aldigiDersler = aldigiDersler;
    }
    return ogrenci;
}

// Öğrenci bilgilerini yazdırma fonksiyonu
void ogrenciYazdir(Ogrenci *ogrenci)
{
    printf("Student Name: %s %s\n", ogrenci->ogrAdi, ogrenci->ogrSoyAdi);
    printf("Department: %s\n", ogrenci->bolumu);
    printf("Average: %.2f\n", ogrenci->ortalama);
}
// Öğrenci dizisini yazdırma fonksiyonu
void ogrenciDiziYazdir(Ogrenci *ogrenciler, int ogrenciSayisi)
{
    for (int i = 0; i < ogrenciSayisi; ++i)
    {
        printf("Student #%d:\n", i + 1);
        ogrenciYazdir(&ogrenciler[i]);
        printf("\n");
    }
}

// Belirli bir dersin ortalama puanını hesaplama fonksiyonu
float dersOrtalama(Ders *dersler, int dersSayisi, char *arananDersAdi)
{
    float toplamPuan = 0;
    int krediToplam = 0;

    for (int i = 0; i < dersSayisi; ++i)
    {
        if (strcmp(dersler[i].dersAdi, arananDersAdi) == 0)
        {
            toplamPuan += dersler[i].puan * dersler[i].kredi;
            krediToplam += dersler[i].kredi;
        }
    }

    return (krediToplam == 0) ? 0 : (toplamPuan / krediToplam);
}

// Belirli bir dersin standart sapmasını hesaplama fonksiyonu
float dersStandartSapma(Ders *dersler, int dersSayisi, char *arananDersAdi)
{
    float ortalama = dersOrtalama(dersler, dersSayisi, arananDersAdi);
    float sumOfSquaredDifferences = 0;

    int count = 0;
    for (int i = 0; i < dersSayisi; ++i)
    {
        if (strcmp(dersler[i].dersAdi, arananDersAdi) == 0)
        {
            sumOfSquaredDifferences += pow(dersler[i].puan - ortalama, 2);
            count++;
        }
    }

    float variance = sumOfSquaredDifferences / count;
    float standardDeviation = sqrt(variance);
    return standardDeviation;
}

// Belirli iki ders arasındaki kovaryansı hesaplama fonksiyonu
float dersKovaryans(Ders *ders1, Ders *ders2, int dersSayisi)
{
    float ders1Ort = 0, ders2Ort = 0;
    float kovaryans = 0;

    for (int i = 0; i < dersSayisi; ++i)
    {
        ders1Ort += ders1[i].puan;
        ders2Ort += ders2[i].puan;
    }

    ders1Ort /= dersSayisi;
    ders2Ort /= dersSayisi;

    for (int i = 0; i < dersSayisi; ++i)
    {
        kovaryans += (ders1[i].puan - ders1Ort) * (ders2[i].puan - ders2Ort);
    }

    return kovaryans / dersSayisi;
}

// Belirli bir derste yüksek not alan öğrencileri listeleme fonksiyonu
void yuksekNotAlanlariListele(Ogrenci *ogrenciler, int ogrenciSayisi, char *arananDersAdi)
{
    printf("Students with high scores in %s:\n", arananDersAdi);
    for (int i = 0; i < ogrenciSayisi; ++i)
    {
        Ders *dersler = ogrenciler[i].aldigiDersler;
        for (int j = 0; j < ogrenciSayisi; ++j)
        {
            if (strcmp(dersler[j].dersAdi, arananDersAdi) == 0 && dersler[j].puan >= 85)
            {
                printf("%s %s\n", ogrenciler[i].ogrAdi, ogrenciler[i].ogrSoyAdi);
                break;
            }
        }
    }
}

// Öğrenci bilgilerini dosyaya yazma fonksiyonu
void ogrenciDosyaYaz(Ogrenci *ogrenciler, int ogrenciSayisi, char *dosyaAdi)
{
    FILE *dosya = fopen(dosyaAdi, "w");
    if (dosya == NULL)
    {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < ogrenciSayisi; ++i)
    {
        fprintf(dosya, "Student Name: %s %s\n", ogrenciler[i].ogrAdi, ogrenciler[i].ogrSoyAdi);
        fprintf(dosya, "Department: %s\n", ogrenciler[i].bolumu);
        fprintf(dosya, "Average: %.2f\n", ogrenciler[i].ortalama);
        fprintf(dosya, "\n");
    }

    fclose(dosya);
}
// Dosyadan öğrenci bilgilerini okuma fonksiyonu
Ogrenci *dosyadanOgrenciOku(char *dosyaAdi, int *ogrenciSayisi)
{
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL)
    {
        return NULL;
    }

    Ogrenci *ogrenciler = NULL; // İlk başta NULL olarak başlatılır
    int index = 0;
    char line[100]; // Buffer boyutu gerektiği gibi ayarlanabilir

    while (fgets(line, sizeof(line), dosya) != NULL)
    {
        char *name = strtok(line, " \n");
        char *surname = strtok(NULL, " \n");

        char *departmentLine = fgets(line, sizeof(line), dosya);
        char *department = strtok(departmentLine, "\n");

        char *averageLine = fgets(line, sizeof(line), dosya);
        float average = atof(averageLine);

        // Her öğrenci için belleği yeniden ayır
        ogrenciler = (Ogrenci *)realloc(ogrenciler, (index + 1) * sizeof(Ogrenci));
        if (ogrenciler == NULL)
        {
            fclose(dosya);
            return NULL;
        }

        ogrenciler[index].ogrAdi = strdup(name);
        ogrenciler[index].ogrSoyAdi = strdup(surname);
        ogrenciler[index].bolumu = strdup(department);
        ogrenciler[index].ortalama = average;

        index++;
    }

    fclose(dosya);
    *ogrenciSayisi = index;

    return ogrenciler;
}
