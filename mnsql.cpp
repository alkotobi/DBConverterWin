#include "mnsql.h"





QString insetSql(const QSqlRecord &rcd,QString tableName)
{

        /*
      INSERT INTO table_name (column1, column2, column3, ...)
      VALUES (value1, value2, value3, ...);
           */
          QString str1=0,str2 ="",str3="";

          for(int i=0;i<rcd.count();i++){
               QSqlField fld= rcd.field(i);
               QString type=fld.value().typeToName(fld.value().type());
               QString strType = type;
               if(str1!="") str1=str1+",";//coma only if have items before
               str1 =str1+"["+fld.name()+"]";
               if(str2!="") str2=str2+",";//coma only if have items before
               if (strType == "QString"){
                   str2=str2+"'"+fld.value().toString()+"'";// if String ,ust add ''
               }else str2=str2+fld.value().toString();

          }
          str1 ="INSERT INTO ["+tableName+"] ("+str1+") ";
          str2 =" VALUES ("+str2+");";



          return str1 + str2;


}


QString MNSql::sqlCreateTable(const QSqlRecord &rcd,QString tableName)
{
    int i=0;
    QString str="CREATE TABLE IF NOT EXISTS '"+tableName+"' (";
    if(rcd.field(0).name()=="ID"){
    str=str+"'ID' INTEGER PRIMARY KEY AUTOINCREMENT,";
    i=1;
    }


       for(;i<rcd.count();i++){
           if (rcd.field(i).isGenerated()){
               QSqlField fld=rcd.field(i);
               QString type=fld.value().typeToName(fld.value().type());
               QString strType =(type=="QString")? "TEXT":type;
               QString str1="'"+fld.name()+"' "+
                       strType;
               if(!(i==rcd.count()-1)){
                   str1=str1+",";
                }
               str =str+str1;
           }
       }

       str=str+");";


       return str;
}

PreparedQueryResult MNSql::sqlInsertPrepared(const QSqlRecord &rcd,QString tableName,QMap<QString,QString> *map){
    /*
  INSERT INTO table_name (column1, column2, column3, ...)
  VALUES (value1, value2, value3, ...);
       */
    //TODO: split prepared sql from values list cze prepared sql will keep same
    PreparedQueryResult ret;
      QString str1="",str2 ="",str3="";
   if(map==nullptr){// if field from dest and source are same definition
      for(int i=0;i<rcd.count();i++){
           QSqlField fld= rcd.field(i);
           QString type=fld.value().typeToName(fld.value().type());
           QString strType = type;
           if(str1!="") str1=str1+",";//coma only if have items before
           str1 =str1+"["+fld.name()+"]";
           if(str2!="") str2=str2+",";//coma only if have items before
               ret.values[":i"+QString::number(i)]=fld.value();
                str2=str2+":i"+QString::number(i);

      }


   }
   else{//with fields mapping
       int i=0;
       foreach(QString key,map->keys()){
           QSqlField fld= rcd.field(map->value(key));
           QString type=fld.value().typeToName(fld.value().type());
           QString strType = type;
           if(str1!="") str1=str1+",";//coma only if have items before
           str1 =str1+"["+key+"]";
           if(str2!="") str2=str2+",";//coma only if have items before
               ret.values[":i"+QString::number(i)]=fld.value();
                str2=str2+":i"+QString::number(i);
                i=i+1;

       }
   }
   str1 ="INSERT INTO ["+tableName+"] ("+str1+") ";
   str2 =" VALUES ("+str2+");";
   ret.preparedSql=str1 + str2;
   return ret;


}

QString MNSql::sqlUpdatePrepared(const QString &tableName,const QString &whereSQl,const QMap<QString, QVariant> &namesAndValues)
{
    QString sql ;
    foreach(QString fieldName,namesAndValues.keys()){
        if(sql!="") sql=sql+",";
        sql=sql+fieldName+"=:"+fieldName;
    }
    sql="UPDATE "+tableName+" SET "+sql+" WHERE "+whereSQl;
    return sql;
}

QString MNSql::sqlInsertPrepared(const QString &tableName,const QMap<QString,QVariant> &namesAndValues){
    QString str1,str2;
    foreach(QString key,namesAndValues.keys()){
        if(str1!="") str1=str1+",";//coma only if have items before
        str1 =str1+"["+key+"]";
        if(str2!="") str2=str2+",";//coma only if have items before
        str2=str2+":"+key;
    }
    str1 ="INSERT INTO ["+tableName+"] ("+str1+") ";
    str2 =" VALUES ("+str2+");";

    return  str1+str2;
}




