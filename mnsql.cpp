#include "mnsql.h"



QString createTableSql(const QSqlRecord &rcd,QString tableName)
{
    QString str="CREATE TABLE IF NOT EXISTS '"+tableName+"' (";



       for(int i=0;i<rcd.count();i++){
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


PreparedQueryResult insertSqlPrepared(const QSqlRecord &rcd,QString tableName){
    /*
  INSERT INTO table_name (column1, column2, column3, ...)
  VALUES (value1, value2, value3, ...);
       */
    PreparedQueryResult ret;
      QString str1=0,str2 ="",str3="";

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
      str1 ="INSERT INTO ["+tableName+"] ("+str1+") ";
      str2 =" VALUES ("+str2+");";
      ret.preparedSql=str1 + str2;



     return ret;


}
