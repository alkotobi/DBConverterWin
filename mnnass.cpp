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
    QString diactrice="ًٌٍَُِّْ";
    QString returnChar =QString('\t')+'\n'+'\v'+'\f'+'\r'+' ';
    Kalimat kalimat;
    QList<MNNass::Kalimat>* list = new QList<MNNass::Kalimat>();
    int i=0;
    //ignore the wrong beginig of nass
    while (returnChar.contains(nass[i]) and i<nass.length()) {
        i++;
    } ;
    for (;i<nass.length();i++) {
//        original= original+nass[i];
        QChar chr =nass[i];
        if(chr.isLetter()){
            norm=norm+chr;
            original= original+chr;
            tachkil=tachkil+"ا";
            continue;
        }else if(diactrice.contains(chr)){
            tachkil=tachkil+chr;
            original= original+chr;
            continue;
        }else if(returnChar.contains(chr)){
            while (returnChar.contains(nass[i]) and i<nass.length()) {
                original= original+chr;
                i++; // must reduce 1 after out this
            } ;
            i--;//previouse while add one more 👆
            bool isTachkil=false;
            foreach(chr,tachkil){
                if (diactrice.contains(chr)){
                    isTachkil =true;
                        break;
            }

            }
            if(not isTachkil) tachkil ="";
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
        }




    }
    quint64 t2 = QDateTime::currentMSecsSinceEpoch();
    MN_SUCCESS(QString::number(t2-t1)+".ms");
    original="";
    norm="";
    tachkil="";

    for (i=0;i<list->count();i++) {

        original = original + list->value(i).original;
        norm=norm+" "+ list->value(i).norm;
        tachkil=tachkil+" "+list->value(i).tachkil;

    }

    MN_INFO(original);
    MN_ERROR(norm);
    MN_WARNING(tachkil);
  return list;
}


