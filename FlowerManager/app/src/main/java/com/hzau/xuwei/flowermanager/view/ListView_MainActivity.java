package com.hzau.xuwei.flowermanager.view;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.hzau.xuwei.flowermanager.R;

public class ListView_MainActivity extends AppCompatActivity {

    private ListView mLv_flower;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_view__main);
        mLv_flower = (ListView) findViewById(R.id.lv_flower);
        mLv_flower.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Toast.makeText(ListView_MainActivity.this,"pos:"+i, Toast.LENGTH_SHORT).show();
            }
        });

        mLv_flower.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, int i, long l) {
                Toast.makeText(ListView_MainActivity.this,"长按pos:"+i, Toast.LENGTH_SHORT).show();
                return true;
            }
        });
    }
}
