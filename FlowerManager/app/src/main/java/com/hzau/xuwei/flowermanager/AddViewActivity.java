package com.hzau.xuwei.flowermanager;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.hzau.xuwei.flowermanager.domain.BmobFlowers;
import com.hzau.xuwei.flowermanager.service.FlowerInfoDao;

import cn.bmob.v3.Bmob;
import cn.bmob.v3.exception.BmobException;
import cn.bmob.v3.listener.SaveListener;

public class AddViewActivity extends AppCompatActivity {
    private Button mBt_add_save;
    private Button mBt_add_back;

    private boolean flagDataValid = false;
    private int itemNumber;
    private TextView mFlower_name;
    private TextView mMonitor_id;
    private TextView mFlower_desc;

    private FlowerInfoDao mFlowerInfoDao;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Bmob 初始化   contest        APP id  flowers类为Bmob用的类  这里不初始化 下面用不了
        Bmob.initialize(this,"7902ee6ffecada8b718604858a813cf6");

        setContentView(R.layout.activity_add_view);
        findID();
        onClickEvent();
        //new 一个FlowerInfoDao
        mFlowerInfoDao = new FlowerInfoDao(AddViewActivity.this);

        //获取MainActivity传过来的item的个数
        Bundle bundle_data = getIntent().getExtras();
        itemNumber = bundle_data.getInt("item_number");
    }

    private void onClickEvent() {
        mBt_add_save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //获取花卉内容
                String flower_name = (String) mFlower_name.getText().toString().trim();  //名字
                String monitor_id = (String) mMonitor_id.getText().toString().trim();  //监测系统ID
                String flower_desc = (String) mFlower_desc.getText().toString().trim();  //描述
                //@TODO 获得Image Button的 URL

                if (TextUtils.isEmpty(flower_name) || TextUtils.isEmpty(monitor_id) || TextUtils.isEmpty(flower_desc)) {
                    Toast.makeText(AddViewActivity.this, "请填写完整的花卉内容", Toast.LENGTH_SHORT).show();
                    return;
                } else {
                    //将新添加的花卉信息添加到数据库
                    mFlowerInfoDao.add(flower_name, monitor_id, flower_desc);
                    //同时在后端云添加数据
                    BmobFlowers bmobFlowers = new BmobFlowers();
                    bmobFlowers.setName(flower_name);
                    bmobFlowers.setMonitor_id(monitor_id);
                    bmobFlowers.setDescribe(flower_desc);
                    bmobFlowers.setHumidity(23);
                    bmobFlowers.save(new SaveListener<String>() {
                        @Override
                        public void done(String s, BmobException e) {  //BmobException不为空 表示插入异常 否则插入成功
                        }
                    });

                    Toast.makeText(AddViewActivity.this, "添加成功", Toast.LENGTH_SHORT).show();
                    //获取MainActivity传过来的item的个数
                    Bundle bundle_data = getIntent().getExtras();
                    itemNumber = bundle_data.getInt("item_number");
                    flagDataValid = true;
                }
            }
        });


        mBt_add_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if (flagDataValid == true) {
                    itemNumber += 1;
                }

                Intent intent_data = new Intent();
                Bundle bundle = new Bundle();
                bundle.putBoolean("valid", flagDataValid);    //数据是否有效标志  点了保存才有效
                bundle.putString("flower_name", "牡丹花");  //@TODO  花的名字需要 get
                bundle.putInt("item_number", itemNumber);  //Item 的个数
                intent_data.putExtras(bundle);
                setResult(Activity.RESULT_OK, intent_data);
                finish();  //结束当前界面
            }
        });
    }


    private void findID() {
        mBt_add_save = (Button) findViewById(R.id.bt_add_save);
        mBt_add_back = (Button) findViewById(R.id.bt_add_back);

        //花卉内容ID
        mFlower_name = (TextView) findViewById(R.id.flower_name);
        mMonitor_id = (TextView) findViewById(R.id.monitor_id);
        mFlower_desc = (TextView) findViewById(R.id.flower_desc);

    }

    public void addSuccess(View view) {
        Toast.makeText(this, "保存成功", Toast.LENGTH_SHORT).show();//short是1秒
    }
}
