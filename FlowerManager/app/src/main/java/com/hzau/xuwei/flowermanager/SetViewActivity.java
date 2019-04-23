package com.hzau.xuwei.flowermanager;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

public class SetViewActivity extends AppCompatActivity {

    private Button mBt_set_back;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set_view);
        mBt_set_back = (Button) findViewById(R.id.bt_set_back);
        mBt_set_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intentToMain = new Intent(SetViewActivity.this, MainActivity.class);
                startActivity(intentToMain);
            }
        });
    }
    
}
