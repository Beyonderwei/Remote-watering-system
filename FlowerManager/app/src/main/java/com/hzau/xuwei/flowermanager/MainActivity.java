package com.hzau.xuwei.flowermanager;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.*;
import cn.bmob.v3.Bmob;
import cn.bmob.v3.BmobQuery;
import cn.bmob.v3.exception.BmobException;
import cn.bmob.v3.listener.FindListener;
import cn.bmob.v3.listener.UpdateListener;
import com.hzau.xuwei.flowermanager.domain.BmobFlowers;
import com.hzau.xuwei.flowermanager.service.FlowerInfoDao;
import com.hzau.xuwei.flowermanager.service.MyDBOpenHelper;
import com.hzau.xuwei.flowermanager.view.MyListAdapter;

import java.util.List;


public class MainActivity extends AppCompatActivity {

    private LinearLayout mLl_loading;
    private ListView mLv_flower;
    private Button mBt_add;
    private Button mBt_inform;
    private Button mBt_me;
    private Button mBt_set;
    private TextView mTv_title;

    private TextView mTv_me_title;
    private MyListAdapter mAdapter;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Bmob 初始化   contest        APP id  flowers类为Bmob用的类
        Bmob.initialize(this, "7902ee6ffecada8b718604858a813cf6");
        //1.  在Bmob后端云插入数据
        /*BmobFlowers rose =new BmobFlowers();
        rose.setName("Rose");
        rose.setMonitor_id("001");
        rose.setDescribe("i am beautiful");
        rose.setHumidity("23");
        rose.save(new SaveListener<String>() {
            @Override
            public void done(String s, BmobException e) {  //BmobException不为空 表示插入异常 否则插入成功
            }
        });*/

        //查询Bmob后端云数据
       /* BmobQuery<BmobFlowers> query =new BmobQuery<>();
        query.getObject("fabc8078d4", new QueryListener<BmobFlowers>() {
            @Override
            public void done(BmobFlowers flowers, BmobException e) {
                Toast.makeText(MainActivity.this,flowers.getName().toString(), Toast.LENGTH_SHORT).show();
            }
        });*/

        //根据指定条件查询数据
        /*BmobQuery<BmobFlowers> query =new BmobQuery<>();
        query.addWhereEqualTo("name","rose");
        query.findObjects(new FindListener<BmobFlowers>() {
            @Override
            public void done(List<BmobFlowers> list, BmobException e) {
                if(e==null){
                    for(BmobFlowers bmobFlowers : list){
                        String s = bmobFlowers.getObjectId();
                    }
                }
            }
        });*/


        //更新Bmob后端云数据
        /*BmobFlowers flowers =new BmobFlowers();
        flowers.setName("xuwei");
        flowers.update("fabc8078d4", new UpdateListener() {
            @Override
            public void done(BmobException e) {

            }
        });*/

        //Bmob删除数据
        /*BmobFlowers bmobFlowers=new BmobFlowers();
        bmobFlowers.setName("name");
        bmobFlowers.delete(new UpdateListener() {
            @Override
            public void done(BmobException e) {
                if(e==null)  //e=null 表示删除成功
                {
                    //先不做操作
                }
            }
        });*/


        //创建数据库
        MyDBOpenHelper helper = new MyDBOpenHelper(this);
        helper.getWritableDatabase(); //调用该方法 在没有数据库的时候 就会自动去创建数据库

        initView();   //初始化界面  寻找控件
        jumpInterface();//跳转界面
        loadFlowerInfo();  //从数据库加载花卉信息
        mLl_loading.setVisibility(View.INVISIBLE);  //让加载界面不可见
        //Toast.makeText(this,"加载数据成功", Toast.LENGTH_SHORT).show();
        System.out.println("Adapter 已执行");
        mAdapter = new MyListAdapter(MainActivity.this);
        mLv_flower.setAdapter(mAdapter);
    }

    /**
     * 在子线程让加载界面显示两秒钟
     */
    private void loadFlowerInfo() {
        new Thread() {
            @Override
            public void run() {
                try {
                    Thread.sleep(1500); //延时2秒
                    mLl_loading.setVisibility(View.INVISIBLE);  //让加载界面不可见
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }.start();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        //@TODO  手机自带返回键使程序崩溃问题
        if (((boolean) data.getExtras().get("valid")) == true) {
            //mTv_me_title.setText(data.getExtras().getString("flower_name"));  //这句仅为了验证传过来的数据对不对 已验证正确
            MyListAdapter adapter = new MyListAdapter(MainActivity.this);
            adapter.mItemNumber = data.getExtras().getInt("item_number");
            mLv_flower.setAdapter(adapter);
        }
    }


    private void jumpInterface() {

        mBt_add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //跳转到Add界面
                Intent intentAdd = new Intent(MainActivity.this, AddViewActivity.class);
                Bundle bundle_to_add = new Bundle();
                bundle_to_add.putInt("item_number", mLv_flower.getCount());  //将当前的item数传过去
                intentAdd.putExtras(bundle_to_add);
                startActivityForResult(intentAdd, 8); //8为返回码  为了从AddViewActivity回调数据
                //startActivity(intentAdd);
            }
        });

        mBt_set.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //跳转到设置界面
                Intent intentSet = new Intent(MainActivity.this, SetViewActivity.class);
                startActivity(intentSet);
            }
        });

        mBt_me.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //跳转到我的花卉界面
                Intent intentMe = new Intent(MainActivity.this, MeViewActivity.class);
                startActivity(intentMe);
            }
        });

        mBt_inform.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //跳转到通知界面
                Intent intentInform = new Intent(MainActivity.this, InformViewActivity.class);
                startActivity(intentInform);
            }
        });

        //ListView的界面跳转
        mLv_flower.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Toast.makeText(MainActivity.this, "pos:" + i, Toast.LENGTH_SHORT).show();
                //获取所点击的item的花卉名称 转化为字符串
                TextView tv_flower_name = (TextView) view.findViewById(R.id.tv_name);
                String name=tv_flower_name.getText().toString();
                //显示跳转1  共有四种  常用这一种
                Intent intentItem = new Intent(MainActivity.this, ListItemActivity.class);
                //每一个item点进去之后是否带数据进去 带数据的话就是下面的代码 验证可用
                Bundle bundle = new Bundle();
                bundle.putBoolean("valid", true);    //数据是否有效标志
                bundle.putString("flower_name", name);  //将所点击的item的花卉名称传递到 item的布局
                intentItem.putExtras(bundle);

                startActivity(intentItem);
                //显示跳转2
                //                Intent intent=new Intent();
                //                intent.setClass(MainActivity.this,ListItemActivity.class);
                //                startActivity(intent);

                //隐式跳转方式   用来调用系统的界面 比如 发短信 打电话...  需要在Manifest中要跳转到的页面添加intent-filter
                //                Intent intent =new Intent();
                //                intent.setAction("jump_To_ListItemActivity");  //setAction可以调用系统的功能
                //                startActivity(intent);
            }
        });

        mLv_flower.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, final View view, int pos, long l) {
                //@TODO 这里通过fragment  画一个对话框显示在这里更好看
                Toast.makeText(MainActivity.this, "长按pos:" + pos, Toast.LENGTH_SHORT).show();
                AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this)
                        .setTitle("删除该盆花？")
                        .setMessage("删除后将无法找回。")
                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                Toast.makeText(MainActivity.this, "删除成功", Toast.LENGTH_SHORT).show();
                                //获取所点击的item花卉在数据库中的name
                                TextView tv_name = (TextView) view.findViewById(R.id.tv_name);
                                String name = tv_name.getText().toString();
                                //new 一个FlowerInfoDao 删除数据库指定的数据
                                FlowerInfoDao mFlowerInfoDao = new FlowerInfoDao(MainActivity.this);
                                mFlowerInfoDao.delete2(name.toString());

                                //查询  根据名字查询ID 根据ID删除数据
                                BmobQuery<BmobFlowers> query = new BmobQuery<>();
                                query.addWhereEqualTo("name", name);
                                query.findObjects(new FindListener<BmobFlowers>() {
                                    @Override
                                    public void done(List<BmobFlowers> list, BmobException e) {
                                        if (e == null) {
                                            for (BmobFlowers bmobFlowers : list) {
                                                bmobFlowers.getObjectId();
                                                bmobFlowers.delete(new UpdateListener() {
                                                    @Override
                                                    public void done(BmobException e) {
                                                        if (e == null)  //e=null 表示删除成功
                                                        {
                                                            //先不做操作
                                                        }
                                                    }
                                                });
                                            }
                                        }
                                    }
                                });



                                /*//Bmob下的数据删除   只能根据花卉ID删除
                                BmobFlowers bmobFlowers = new BmobFlowers();
                                bmobFlowers.setObjectId("8ccedd60d3");
                                bmobFlowers.delete(new UpdateListener() {
                                    @Override
                                    public void done(BmobException e) {
                                        if (e == null)  //e=null 表示删除成功
                                        {
                                            //先不做操作
                                        }
                                    }
                                });*/

                                System.out.println("长按所获得的name：" + name.toString());
                                mLv_flower.setAdapter(mAdapter);
                                //@TODO 删除该位置的Item
                            }
                        })
                        .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                //不做任何操作
                            }
                        });
                builder.show();//调用该方法来显示出对话框

                return true;//返回值为true  可避免长按后仍然执行点击事件 
            }
        });
    }


    /**
     * 初始化界面
     */
    private void initView() {
        setContentView(R.layout.activity_main);  //加载MainActivity
        //寻找控件：
        //1.mainActivity中的控件
        mBt_add = (Button) findViewById(R.id.bt_add);
        mBt_inform = (Button) findViewById(R.id.bt_inform);
        mBt_me = (Button) findViewById(R.id.bt_me);
        mBt_set = (Button) findViewById(R.id.bt_set);
        mTv_title = (TextView) findViewById(R.id.tv_name);

        mLl_loading = (LinearLayout) findViewById(R.id.ll_loading);
        mLv_flower = (ListView) findViewById(R.id.lv_flower);
        mLl_loading.setVisibility(View.VISIBLE);   //使List View可见


        mTv_me_title = (TextView) findViewById(R.id.tv_name);
    }


}


//    <?xml version="1.0" encoding="utf-8"?>
//<paths xmlns:android ="http://schemas.android.com/apk/res/android">
//<external-path
//        name="my_images"
//        path="android.com/apk/res/android"/>  //这里可能有问题
//</paths>