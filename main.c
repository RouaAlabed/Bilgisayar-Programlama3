/*

* @file proje
* @description Genel olarak, bu kod yapısı dersleri ve öğrencileri yönetmek,
    istatistikleri hesaplamak, onlar üzerinde işlemler yapmak ve dosya giriş/çıkış
    işlemlerini ele almak için işlevsellik sağlar.
* @assignment odev1
* @date 08/12/2023
* @author Rüya ALABED
    roua.alabed@stu.fsm.edu.tr

*/

#include <stdio.h>
#include <stdlib.h>
#include "proje1.h"

int main()
{
    // Ders (Course) örneklerini oluşturma
    Ders *ders1 = dersOlustur("Math", 5, 90);
    Ders *ders2 = dersOlustur("Physics", 4, 85);
    Ders *ders3 = dersOlustur("Chemistry", 3, 75);

    // Ders örneklerinden bir dizi oluşturma
    Ders dersler[] = {*ders1, *ders2, *ders3};
    int dersSayisi = 3;

    // Belirli bir ders için ortalama puanı hesaplama ve yazdırma
    char *arananDersAdi = "Physics";
    float ortalama = dersOrtalama(dersler, dersSayisi, arananDersAdi);
    printf("Average score in %s: %.2f\n", arananDersAdi, ortalama);

    // Belirli bir ders için standart sapmayı hesaplama ve yazdırma
    float standartSapma = dersStandartSapma(dersler, dersSayisi, arananDersAdi);
    printf("Standard deviation in %s: %.2f\n", arananDersAdi, standartSapma);

    // Öğrenci (Student) örneklerini oluşturma
    Ders ogrenci1_dersler[] = {*ders1, *ders2};
    Ogrenci *ogrenci1 = ogrenciOlustur("Ali", "Muhammad", "Engineering", 85.0, ogrenci1_dersler);

    Ders ogrenci2_dersler[] = {*ders2, *ders3};
    Ogrenci *ogrenci2 = ogrenciOlustur("Sumeye", "Karam", "Science", 78.5, ogrenci2_dersler);

    // Öğrenci örneklerinden bir dizi oluşturma
    Ogrenci ogrenciler[] = {*ogrenci1, *ogrenci2};
    int ogrenciSayisi = 2;

    // Öğrenci bilgilerini yazdırma
    ogrenciDiziYazdir(ogrenciler, ogrenciSayisi);

    // Belirli bir dersi yüksek puan alan öğrencileri listeleme
    yuksekNotAlanlariListele(ogrenciler, ogrenciSayisi, arananDersAdi);

    // Öğrenci bilgilerini dosyaya yazma
    ogrenciDosyaYaz(ogrenciler, ogrenciSayisi, "students.txt");

    // Dosyadan öğrenci bilgilerini okuma
    int dosyadanOkunanOgrenciSayisi = 0;
    Ogrenci *okunanOgrenciler = dosyadanOgrenciOku("students.txt", &dosyadanOkunanOgrenciSayisi);
    if (okunanOgrenciler != NULL)
    {
        ogrenciDiziYazdir(okunanOgrenciler, dosyadanOkunanOgrenciSayisi);
        free(okunanOgrenciler); // Remember to free allocated memory
    }
    else
    {
        printf("Error reading students from file.\n");
    }

    // Ayrılan belleği serbest bırakma (dersler için)
    free(ders1);
    free(ders2);
    free(ders3);

    // Ayrılan belleği serbest bırakma (öğrenciler için)
    free(ogrenci1->aldigiDersler);
    free(ogrenci1);
    free(ogrenci2->aldigiDersler);
    free(ogrenci2);

    return 0;
}
