package com.hzau.xuwei.flowermanager;

import android.content.Intent;
import android.graphics.Rect;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.hzau.xuwei.flowermanager.view.MeRvAdapter;

public class MeViewActivity extends AppCompatActivity {

    private Button mBt_me_back;
    private RecyclerView mRv_me;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_me_view);

        mBt_me_back = (Button) findViewById(R.id.bt_me_back);
        mRv_me = (RecyclerView) findViewById(R.id.rv_me);

        mBt_me_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intentBack = new Intent(MeViewActivity.this, MainActivity.class);
                startActivity(intentBack);
            }
        });


        //线性布局管理器
        mRv_me.setLayoutManager(new LinearLayoutManager(MeViewActivity.this));

        //添加分隔线  分隔线的颜色就是RecyclerView的背景的颜色
        mRv_me.addItemDecoration(new MeViewActivity.MyDecoration());

        //RecycleView的适配器
        //传入一个在Adapter类（自己写的）中 创建的Adapter 这里实际是一个LinearAdapter
        //并实现每一个Item的点击事件 通过自己在Adapter中写的接口实现 这样其他的也可以调这个
        mRv_me.setAdapter(new MeRvAdapter(MeViewActivity.this, new MeRvAdapter.OnItemClickListener() {
            @Override
            public void onClick(int pos) {
                Toast.makeText(MeViewActivity.this, "我是第" + pos + "个List", Toast.LENGTH_SHORT).show();
            }
        }));
    }


    class MyDecoration extends RecyclerView.ItemDecoration {
        @Override
        public void getItemOffsets(Rect outRect, View view, RecyclerView parent, RecyclerView.State state) {
            super.getItemOffsets(outRect, view, parent, state);
            //这里只在下面设置分割线    dividerHeight_1 定义在values 下高度为1dp 只需要在上面添加分割线处new一个 MyDecoration的对象传入即可
            outRect.set(0, 0, 0, getResources().getDimensionPixelOffset(R.dimen.dividerHeight_10));
        }
    }
}



