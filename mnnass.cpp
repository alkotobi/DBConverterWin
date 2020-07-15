#include "mnnass.h"

MNNass::MNNass()
{

}

QList<MNNass::Kalimat>* MNNass::getKalimat(const QString &nass)
{
    quint64 t1 = QDateTime::currentMSecsSinceEpoch();
    QString tachkil;
    QString original;
    QString norm;
    //QString diactrice="ًٌٍَُِّْ";//1611>>1618

    //QString returnChar =QString('\t')+'\n'+'\v'+'\f'+'\r'+' ';//9>>13 and 32
    Kalimat kalimat;
    int nass_length=nass.length();
    QList<MNNass::Kalimat>* list = new QList<MNNass::Kalimat>();
    int i=0;
    //ignore the wrong beginig of nass
    while (nass[i].isSpace() && i<nass_length) {
        i++;
    } ;
    for (;i<nass_length;i++) {
//        original= original+nass[i];
        QChar chr =nass[i];
        if(chr.isLetter()){
            norm=norm+chr;
            original= original+chr;
            tachkil=tachkil+"ا";
            continue;
        }else if(chr>=1611 && chr<=1618){
            tachkil=tachkil+chr;
            original= original+chr;
            continue;
        }else if(chr.isSpace()){
            while (nass[i].isSpace() && i<nass_length) {
                original= original+chr;
                i++; // must reduce 1 after out this
            } ;
            i--;//previouse while add one more 👆
            bool isTachkil=false;
            foreach(chr,tachkil){
                if (chr>=1611 && chr<=1618){
                    isTachkil =true;
                        break;
            }

            }
            if(! isTachkil) tachkil ="";
            kalimat.norm=norm;
            kalimat.tachkil=tachkil;
            kalimat.original=original;
            (*list)<<kalimat;
            original="";
            norm="";
            tachkil="";
            continue;

        }else{
          original= original+chr;
          if(i==nass_length-1){
              kalimat.norm=norm;
              kalimat.tachkil=tachkil;
              kalimat.original=original;
              (*list)<<kalimat;
              original="";
              norm="";
              tachkil="";
          }
        }




    }
    quint64 t2 = QDateTime::currentMSecsSinceEpoch();
    MN_SUCCESS(QString::number(t2-t1)+".ms");
    original="";
    norm="";
    tachkil="";


  return list;
}


