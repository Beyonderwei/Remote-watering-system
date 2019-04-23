package com.hzau.xuwei.flowermanager.service;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * @version $Rev$
 * @auther Administrator
 * @des ${TODO}
 * @updataAuthor $Author$
 * @updateDes ${TODO}
 */

public class MyDBOpenHelper extends SQLiteOpenHelper {
    public MyDBOpenHelper(Context context) {
        //第一个参数是上下文
        //第二个参数是数据库名称
        //第三个参数null表示默认的游标工厂
        //第四个参数是数据库的版本号 数据库只能升级 不能降级 版本号只能变大不能变小
        super(context,"hua-mi-shu",null,1);
    }

    /**
     * Called when the database is created for the fist time.
     * 当数据库第一次被创建的时候被调用的方法 适合在这个方法里把数据库的表结构定义出来 只调用一次
     * @param sqLiteDatabase
     */
    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        System.out.println("onCreate 数据库被创建了");
        sqLiteDatabase.execSQL("create table lv_flower_info(id integer primary key autoincrement,name varchar(20),monitor_id varchar(20),describe varchar(20)); ");

    }

    /**
     * Called when the database needs to be upgrade.
     * 当数据库更新的时候调用的方法 改变一次版本号 这个方法就会调用一次 且下一次不会再调用
     * @param sqLiteDatabase
     * @param i
     * @param i1
     */
    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {
        System.out.println("onUpgrade 数据库被更新了");
        sqLiteDatabase.execSQL("alter table contactinfo add monitor_id varchar(20);");
    }
}