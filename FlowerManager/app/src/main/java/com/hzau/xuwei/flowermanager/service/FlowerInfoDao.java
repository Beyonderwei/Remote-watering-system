package com.hzau.xuwei.flowermanager.service;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

import com.hzau.xuwei.flowermanager.domain.Flower;

import java.util.ArrayList;

/**
 * @version $Rev$
 * @auther Administrator
 * @des ${TODO}
 * @updataAuthor $Author$
 * @updateDes ${TODO}
 */

public class FlowerInfoDao {

    private final MyDBOpenHelper mHelper;

    public FlowerInfoDao(Context context) {
        mHelper = new MyDBOpenHelper(context);
    }

    /**
     * 添加一条记录
     *
     * @param name       花卉名称
     * @param monitor_id 花卉图片路径或 url
     * @param describe   花卉的描述
     */
    public void add(String name, String monitor_id, String describe) {
        SQLiteDatabase db = mHelper.getWritableDatabase();
        db.execSQL("insert into lv_flower_info(name,monitor_id,describe) values (?,?,?);", new Object[]{name, monitor_id, describe});
        //关闭数据库释放资源
        db.close();
    }

    /**
     * 删除一条记录 根据花卉ID
     *
     * @param id 联系人姓名
     */
    public void delete(int id) {
        SQLiteDatabase db = mHelper.getWritableDatabase();
        System.out.println("当前ID："+id);
        db.execSQL("delete from lv_flower_info where id=?;", new Object[]{id});
        //记得关闭数据库释放资源
        db.close();
    }

    /**
     * 删除一条记录  根据name属性
     *
     * @param name 联系人姓名
     */
    public void delete2(String name) {
        SQLiteDatabase db = mHelper.getWritableDatabase();
        //System.out.println("当前ID："+name);
        db.execSQL("delete from lv_flower_info where name=?;", new Object[]{name});
        //记得关闭数据库释放资源
        db.close();
    }



    /**
     * 修改花卉名称和监测系统ID  根据花的名字去改
     *
     * @param new_monitor_id 监测系统ID
     * @param name           花卉名称
     */
    public void update(String new_monitor_id, String name) {
        SQLiteDatabase db = mHelper.getWritableDatabase();
        db.execSQL("update lv_flower_info set monitor_id=? where name=? ;", new Object[]{new_monitor_id, name});
        //关闭数据库释放资源
        db.close();
    }

    /**
     * 查询花卉对应监测系统ID 根据花卉的名字去查
     *
     * @param id 花卉id  数据库默认的排序
     */
    public String[] query(int id) {
        String s = String.valueOf(id);  //将id转化为字符串类型
        SQLiteDatabase db = mHelper.getReadableDatabase();
        Cursor cursor = db.rawQuery("select name,monitor_id,describe from lv_flower_info where id=?;", new String[]{s});
        String date[] = new String[3];
        if (cursor.moveToNext()) {
            date[0] = cursor.getString(0);
            date[1] = cursor.getString(1);
            date[2] = cursor.getString(2);
        }
        //关闭数据库释放资源
        cursor.close();
        db.close();
        return date;
    }





    private ArrayList<Flower> data;

    /**
     * 查询数据库中所有数据
     */
    public ArrayList<Flower> queryAll() {
        data=new ArrayList<Flower>();

        SQLiteDatabase db = mHelper.getReadableDatabase();
        Cursor cursor = db.query("lv_flower_info",null,null,null,null,null,null,null);
        while(cursor.moveToNext()) {
            String name = cursor.getString(1);
            String monitor_id= cursor.getString(2);
            String describe = cursor.getString(3);

            Flower f = new Flower(name,monitor_id,describe);
            data.add(f);
        }
        //关闭数据库释放资源
        cursor.close();
        db.close();
        return data;
    }

    /**
     * 返回数据库中数据个数
     * @return
     */
    public int getCount(){
        SQLiteDatabase db = mHelper.getReadableDatabase();
        Cursor cursor = db.query("lv_flower_info",null,null,null,null,null,null);
        int count = cursor.getCount();//记录条数
        return count;
    }
}
