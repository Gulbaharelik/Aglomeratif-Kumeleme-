#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Tanımlamalar yapılır.
struct kume {
    float x;
    float y;
    int kume_atama;
};

//Kümeler arası mesafe hesaplanır.
float mesafe_hesabi(struct kume kume1, struct kume kume2) {
    return sqrt(pow(kume1.x - kume2.x, 2) + pow(kume1.y - kume2.y, 2));
}

//Kumelerin ortalaması alınıp yeni kumeler oluşturulur.
struct kume gecici_kumeler(struct kume kume1, struct kume kume2) {
    struct kume gecici;
   gecici.x = (kume1.x + kume2.x) / 2;
    gecici.y = (kume1.y + kume2.y) / 2;
    return gecici;
}

//Küme değerleri.
int main() {
	int i,j;
    int sayi_degerler = 7;
    struct kume degerler[] = {
        {19, 15, 1},
        {21, 15, 1},
        {20, 16, 1},
        {23, 16, 1},
        {31, 17, 1},
        {22, 17, 1},
        {35, 18, 1}
    };
printf("\n");    
printf("******MALL_CUSTOMERS yaslari ve yillik geliri bulunan 7 kisinin toplayici hiyerarsik kumelemesi****\n");
printf("\n");

    // Hiyerarşik birleştirici kümeleme işlemi yapılır.
    int sayi_kumeleme = sayi_degerler;
    struct kume kumeler[sayi_degerler];
    for ( i = 0; i < sayi_degerler; i++) {
        kumeler[i] = degerler[i];
    }

    while (sayi_kumeleme > 1) {
        // En yakın iki küme bulunur.
        float orta_mesafe = INFINITY;
        int orta_deger1, orta_deger2;

        for ( i = 0; i < sayi_kumeleme -1; i++) {
            for (j = i + 1; j < sayi_kumeleme; j++) {
                float mesafe = mesafe_hesabi(kumeler[i], kumeler[j]);
                if (mesafe <orta_mesafe) {
                    orta_mesafe= mesafe;
                    orta_deger1 = i;
                    orta_deger2 = j;
                }
            }
        }

        // İki küme birleştirilir.
        struct kume gecici_kumeleme=gecici_kumeler(kumeler[orta_deger1], kumeler[orta_deger2]);
        gecici_kumeleme.kume_atama = (sayi_degerler - sayi_kumeleme )+ 1;

        // Birleştirilen kümeyle birlikte küme listesini güncelleme
        kumeler[orta_deger1] =gecici_kumeleme;
        for (i = orta_deger2; i < sayi_kumeleme - 1; i++) {
            kumeler[i] = kumeler[i + 1];
        }

        sayi_kumeleme--;

        // Kümeleme ayrıntıları yazdırılır.
        printf("Adim %d:\n",(sayi_degerler - sayi_kumeleme));
        for ( i = 0; i < sayi_kumeleme; i++) {
            printf("Kume sayisi:%d: (%.2f, %.2f)\n", kumeler[i].kume_atama, kumeler[i].x, kumeler[i].y);
        }
        printf("\n");
    }
    
	return 0;
}
