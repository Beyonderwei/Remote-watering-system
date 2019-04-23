package com.hzau.xuwei.flowermanager;

import android.content.Intent;
import android.graphics.Rect;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.hzau.xuwei.flowermanager.view.Adapter;

public class InformViewActivity extends AppCompatActivity {

    private RecyclerView mRv_inform;
    private Button mBt_inform_back;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_inform_view);
        mRv_inform = (RecyclerView) findViewById(R.id.rv_inform);


        mBt_inform_back = (Button) findViewById(R.id.bt_inform_back);

        mBt_inform_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intentBack = new Intent(InformViewActivity.this, MainActivity.class);
                startActivity(intentBack);
            }
        });


        //线性布局管理器
        mRv_inform.setLayoutManager(new LinearLayoutManager(InformViewActivity.this));

        //添加分隔线  分隔线的颜色就是RecyclerView的背景的颜色
        mRv_inform.addItemDecoration(new MyDecoration());

        //RecycleView的适配器
        //传入一个在Adapter类（自己写的）中 创建的Adapter 这里实际是一个LinearAdapter
        //并实现每一个Item的点击事件 通过自己在Adapter中写的接口实现 这样其他的也可以调这个
        mRv_inform.setAdapter(new Adapter(InformViewActivity.this, new Adapter.OnItemClickListener() {
            @Override
            public void onClick(int pos) {
                Toast.makeText(InformViewActivity.this,"我是第" + pos + "个List", Toast.LENGTH_SHORT).show();
            }
        }));

    }

    class MyDecoration extends RecyclerView.ItemDecoration{
        @Override
        public void getItemOffsets(Rect outRect, View view, RecyclerView parent, RecyclerView.State state) {
            super.getItemOffsets(outRect, view, parent, state);
            //这里只在下面设置分割线    dividerHeight_1 定义在values 下高度为1dp 只需要在上面添加分割线处new一个 MyDecoration的对象传入即可
            outRect.set(0,0,0,getResources().getDimensionPixelOffset(R.dimen.dividerHeight_2));
        }
    }


    //activity生命周期所执行的方法  根据日志调试
    @Override
    protected void onStart() {
        super.onStart();
        Log.d("LifeCycle","-------onStart-----");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d("LifeCycle","-------onResume-----");
        //每次进来这个界面 要刷新数据的功能在这里写  因为每次进来都会执行这个方法

    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d("LifeCycle","-------onPause-----");
        //APP跳到后台执行时会执行这个方法 也会执行Onstop方法  这时需要做 ：比如将歌曲 电影暂停

    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d("LifeCycle","-------onStop-----");

    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.d("LifeCycle","-------onRestart-----");

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d("LifeCycle","-------onDestroy-----");
        //界面摧毁之前要做的东西

    }

}
