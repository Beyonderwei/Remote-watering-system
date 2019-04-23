package com.hzau.xuwei.flowermanager;

import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.support.v4.content.FileProvider;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import com.hzau.xuwei.flowermanager.utils.StreamUtils;
import org.json.JSONArray;
import org.json.JSONObject;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class ListItemActivity extends AppCompatActivity implements View.OnClickListener {
    //当前花卉ID
    private String mFlower_ID;
    //当前ListItem 的花卉名称
    private String mFlower_name;
    //当前花卉Item的浇水量
    private int mBulk = 0;
    //屏幕适配高宽
    private int screenWidth;
    private int mScreenHeight;
    //浇水量是否被按下标志位
    boolean flag_50ml = false;
    boolean flag_100ml = false;
    boolean flag_150ml = false;
    boolean flag_200ml = false;
    //布局控件
    private ImageView mIv_my_flower_1;
    private ImageView mIv_my_flower_2;
    private ImageView mIv_my_flower_3;
    private TextView mTv_item_title;
    private TextView mTv_edit;
    private Button mBt_item_back;
    private TextView mTv_humidity;
    private TextView mTv_temperature;
    private TextView mTv_co2;
    private TextView mTv_status;
    private Button mBt_50ml;
    private Button mBt_100ml;
    private Button mBt_150ml;
    private Button mBt_200ml;
    private Button mBt_ensure;
    private Button mBt_cancel;
    private static final int STATUS_SUCCESS = 1;
    private static final int STATUS_ERROR = 0;

    private Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case STATUS_SUCCESS:

                    break;
                case STATUS_ERROR:
                    System.out.println("登录失败");
                    break;

                default:
                    break;
            }
        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_item);
        //1.寻找控件
        initView();

        //2.适配屏幕
        DisplayMetrics dm = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm); //获取屏幕信息
        screenWidth = dm.widthPixels;
        mScreenHeight = dm.heightPixels;
        mIv_my_flower_1.setImageResource(R.drawable.rose); //@TODO 通过URL的方式显示网络上的图片
        mIv_my_flower_2.setImageResource(R.drawable.rose); //@TODO 通过URL的方式显示网络上的图片
        mIv_my_flower_3.setImageResource(R.drawable.rose); //@TODO 通过URL的方式显示网络上的图片
        ViewGroup.LayoutParams params_1 = mIv_my_flower_1.getLayoutParams();
        ViewGroup.LayoutParams params_2 = mIv_my_flower_2.getLayoutParams();
        ViewGroup.LayoutParams params_3 = mIv_my_flower_3.getLayoutParams();
        params_1.width = params_2.width = params_3.width = screenWidth;
        params_1.height = params_2.height = params_3.height = mScreenHeight / 3;
        mIv_my_flower_1.setLayoutParams(params_1);
        mIv_my_flower_2.setLayoutParams(params_2);
        mIv_my_flower_3.setLayoutParams(params_3);

        //3.接收数据 由MainActivity 传过来的数据 不一定用得到 已验证可以使用  传过来的数据没有影响 暂留
        Bundle bundle_data = getIntent().getExtras();
        boolean valid = bundle_data.getBoolean("valid");
        mFlower_name = bundle_data.getString("flower_name");
        mTv_item_title.setText(mFlower_name);  //将上面的标题设置为花卉的名称


        new Thread() {
            @Override
            public void run() {
                //查询服务器 得到花卉的信息 自己的linux服务器    安卓4.0以后必须在子线程中下面这段 防止主线程卡
                try {
                    String urlPath = "http://192.168.1.100:8080/appQuery?flower_name=" + mFlower_name;
                    URL url = new URL(urlPath);
                    HttpURLConnection coon = (HttpURLConnection) url.openConnection();
                    coon.setRequestMethod("GET");
                    coon.setConnectTimeout(5000);
                    //System.out.println("徐威徐威");
                    int code = coon.getResponseCode();
                    if (code == 200) {
                        //1.得到输入流
                        InputStream is = coon.getInputStream();
                        //2.将流用自己写的StreamUtils转化为字符串  改字符串为json格式
                        String flowerInfo = StreamUtils.readStream(is);
                        //3.解析json数据（这里是数组的形式）  并显示数据
                        JSONArray flowerJsonArray = new JSONArray(flowerInfo);
                        //System.out.println("数组长度："+flowerJsonArray.length());
                        for (int i = 0; i < flowerJsonArray.length(); i++) {
                            JSONObject flowerJsonObject = flowerJsonArray.getJSONObject(i);
                            mTv_temperature.setText(flowerJsonObject.getString("temperature"));//温度
                            mTv_humidity.setText(flowerJsonObject.getString("humidity"));//湿度
                            mTv_co2.setText(flowerJsonObject.getString("co2"));//CO2 浓度
                        }
                    } else {
                        Message msg = Message.obtain();
                        msg.what = STATUS_ERROR;
                        mHandler.sendMessage(msg);
                    }

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }.start();


        //下面这段是应该加上的，属于Bmob的数据服务  这里为了测试自己的服务器  把这段屏蔽掉
        /*//根据 mainActivity 传过来的名字去查询花卉的 湿度 缺水状态 然后显示到界面
        BmobQuery<BmobFlowers> query = new BmobQuery<>();
        query.addWhereEqualTo("name", flower_name);
        query.findObjects(new FindListener<BmobFlowers>() {
            @Override
            public void done(List<BmobFlowers> list, BmobException e) {
                if (e == null) {
                    for (BmobFlowers bmobFlowers : list) {
                        //从数据库查询花卉数据
                        mFlower_ID =bmobFlowers.getObjectId();  //花卉ID
                        String desc = bmobFlowers.getDescribe();  //描述
                        Number temp = bmobFlowers.getTemperature();  //温度
                        mTv_temperature.setText(temp.toString());
                        Number humidity = bmobFlowers.getHumidity();  //湿度
                        mTv_humidity.setText(humidity.toString());
                        boolean flag_wartering = bmobFlowers.getFlag_watering();  //浇水标志位
                        Number co2 = bmobFlowers.getCo2();  //CO2 浓度
                        mTv_co2.setText(co2.toString());
                        Number bulk = bmobFlowers.getBulk();  //浇水量
                        String monitor_id = bmobFlowers.getMonitor_id();  //监测系统ID
                    }
                }
            }
        });*/
    }

    //拍照所需成员变量
    public static final int TAKE_PHOTO = 1;
    private Uri imageUri;

    //设置点击事件
    @Override
    public void onClick(View view) {
        Intent intent = null;
        switch (view.getId()) {
            case R.id.tv_edit: {
                //Toast.makeText(this,"我被点击了", Toast.LENGTH_SHORT).show();
                //工厂设计模式 得到创建对话框的工厂
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                //builder.setTitle("请选择您的姓别：");
                final String[] items = {"拍照", "从相册选择图片"};
                builder.setSingleChoiceItems(items, -1, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        Toast.makeText(ListItemActivity.this, "您选择的方式是：" + items[i], Toast.LENGTH_SHORT).show();

                        //i=0   打开相机拍照
                        if (i == 0) {
                            File outputImage = new File(getExternalCacheDir(), "output_image.jpg");
                            try {
                                if (outputImage.exists()) {
                                    outputImage.delete();
                                }
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                            if (Build.VERSION.SDK_INT >= 24) {
                                imageUri = FileProvider.getUriForFile(ListItemActivity.this, "com.flowermanager.cameraalbumtest.fileprovider", outputImage);
                            } else {
                                imageUri = Uri.fromFile(outputImage);
                            }
                            //启动相机
                            Intent intent1 = new Intent("android.media.action.IMAGE_CAPTURE");
                            intent1.putExtra(MediaStore.EXTRA_OUTPUT, imageUri);
                            startActivityForResult(intent1, TAKE_PHOTO);
                        }
                        //i=1 到手机中选择照片  @TODO 去相册选择照片的程序


                        dialogInterface.dismiss();
                    }
                });
                builder.show(); //show方法中调用了creat方法
                break;
            }
            case R.id.bt_item_back: {
                Intent intentToMain = new Intent(ListItemActivity.this, MainActivity.class);
                startActivity(intentToMain);
                break;
            }
            case R.id.bt_50ml: {
                if (flag_50ml == false) {
                    mBt_50ml.setBackground(new ColorDrawable(Color.RED));
                    flag_50ml = true;
                } else {
                    mBt_50ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_50ml = false;
                }
                break;
            }
            case R.id.bt_100ml: {
                if (flag_100ml == false) {
                    mBt_100ml.setBackground(new ColorDrawable(Color.RED));
                    flag_100ml = true;
                } else {
                    mBt_100ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_100ml = false;
                }
                break;
            }
            case R.id.bt_150ml: {
                if (flag_150ml == false) {
                    mBt_150ml.setBackground(new ColorDrawable(Color.RED));
                    flag_150ml = true;
                } else {
                    mBt_150ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_150ml = false;
                }
                break;
            }
            case R.id.bt_200ml: {
                if (flag_200ml == false) {
                    mBt_200ml.setBackground(new ColorDrawable(Color.RED));
                    flag_200ml = true;
                } else {
                    mBt_200ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_200ml = false;
                }
                break;
            }
            case R.id.bt_ensure: {
                //根据用户输入的浇水量 将浇水量返回给服务器
                mBulk=0;    //每次点击确定前先将浇水量置为0
                if (flag_50ml == true)
                    mBulk += 50;
                if (flag_100ml == true)
                    mBulk += 100;
                if (flag_150ml == true)
                    mBulk += 150;
                if (flag_200ml == true)
                    mBulk += 200;
                if (mBulk == 0) {
                    Toast.makeText(this, "请选择浇水量", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(this, "浇水成功", Toast.LENGTH_SHORT).show();
                    /*--将总的浇水量等信息上传到服务器 更新服务器数据--*/
                    /*云服务器的方式*/
                    new Thread() {
                        @Override
                        public void run() {
                            //查询服务器 得到花卉的信息 自己的linux服务器    安卓4.0以后必须在子线程中下面这段 防止主线程卡
                            try {
                                String urlPath = "http://192.168.1.100:8080/appPost";  //向服务器发送 post 请求
                                URL url = new URL(urlPath);
                                HttpURLConnection coon = (HttpURLConnection) url.openConnection();
                                coon.setRequestMethod("POST");
                                coon.setConnectTimeout(5000);
                                coon.setRequestProperty("Content-Type", "application/json");     //设置发送的数据为 json 类型，会被添加到http body当中
                                String json = "{\"name\":\""+ mFlower_name+"\"," + "\"bulk\":" + "\"" +mBulk+ "\"}";    //将要发送的花卉数据连接成json格式
                                coon.setRequestProperty("Content-Length", String.valueOf(json.length()));

                                //post请求把数据以流的方式写给服务器
                                //指定请求的输出模式
                                coon.setDoOutput(true);
                                coon.getOutputStream().write(json.getBytes());

                                int code = coon.getResponseCode();
                                if (code == 200) {
                                    /*//1.得到输入流
                                    InputStream is = coon.getInputStream();
                                    //2.将流用自己写的StreamUtils转化为字符串
                                    String flowerInfo = StreamUtils.readStream(is);
                                    System.out.println(flowerInfo);*/
                                    System.out.println("请求成功");
                                } else {
                                    System.out.println("请求失败");
                                }

                            } catch (Exception e) {
                                e.printStackTrace();
                                System.out.println("请求失败");
                            }
                        }
                    }.start();

                    //下面时使用Bmob的方式 可以用
                    /*BmobFlowers bmobFlowers = new BmobFlowers();
                    bmobFlowers.setBulk(bulk);  //更新浇水量
                    bmobFlowers.setFlag_watering(true);  //更新浇水标志位
                    bmobFlowers.update(mFlower_ID, new UpdateListener() {
                        @Override
                        public void done(BmobException e) {

                        }
                    });*/
                    //将浇水选择按钮还原成灰色状态
                    mBt_50ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_50ml = false;
                    mBt_100ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_100ml = false;
                    mBt_150ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_150ml = false;
                    mBt_200ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                    flag_200ml = false;
                }


                break;
            }
            case R.id.bt_cancel: {
                //将浇水选择按钮还原成灰色状态
                mBt_50ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                flag_50ml = false;
                mBt_100ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                flag_100ml = false;
                mBt_150ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                flag_150ml = false;
                mBt_200ml.setBackgroundColor(Color.parseColor("#d6d7d7"));
                flag_200ml = false;
                break;
            }
        }
    }

    /**
     * 寻找控件 设置点击事件
     */
    public void initView() {
        /*-----------------------寻找控件-----------------------*/
        //1.花卉名称展示按钮 返回键按钮
        mTv_item_title = (TextView) findViewById(R.id.tv_name);
        mBt_item_back = (Button) findViewById(R.id.bt_item_back);
        //2.花卉展示图片控件
        mIv_my_flower_1 = (ImageView) findViewById(R.id.iv_my_flower_1);
        mIv_my_flower_2 = (ImageView) findViewById(R.id.iv_my_flower_2);
        mIv_my_flower_3 = (ImageView) findViewById(R.id.iv_my_flower_3);
        //3.编辑照片的textview
        mTv_edit = (TextView) findViewById(R.id.tv_edit);
        //4.花卉数据控件
        mTv_humidity = (TextView) findViewById(R.id.tv_humidity);  //湿度
        mTv_temperature = (TextView) findViewById(R.id.tv_temperature);  //温度
        mTv_co2 = (TextView) findViewById(R.id.tv_co2);  //CO2浓度
        mTv_status = (TextView) findViewById(R.id.tv_status);  //花卉缺水状态
        //4.浇水量
        mBt_50ml = (Button) findViewById(R.id.bt_50ml);
        mBt_100ml = (Button) findViewById(R.id.bt_100ml);
        mBt_150ml = (Button) findViewById(R.id.bt_150ml);
        mBt_200ml = (Button) findViewById(R.id.bt_200ml);
        //5.确定取消按钮
        mBt_ensure = (Button) findViewById(R.id.bt_ensure);
        mBt_cancel = (Button) findViewById(R.id.bt_cancel);

        /*------------------------设置点击事件----------------------*/
        mBt_item_back.setOnClickListener(this);  //返回
        mTv_edit.setOnClickListener(this);  //编辑照片
        mBt_50ml.setOnClickListener(this);  //50ml浇水按钮
        mBt_100ml.setOnClickListener(this);  //50ml浇水按钮
        mBt_150ml.setOnClickListener(this);  //50ml浇水按钮
        mBt_200ml.setOnClickListener(this);  //50ml浇水按钮
        mBt_ensure.setOnClickListener(this);
        mBt_cancel.setOnClickListener(this);
    }

    /**
     * 拍照服务用的  忘记了 参考Android第一行代码
     *
     * @param requestCode
     * @param resultCode
     * @param data
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case TAKE_PHOTO:
                if (resultCode == RESULT_OK) {
                    try {
                        Bitmap bitmap = BitmapFactory.decodeStream(getContentResolver().openInputStream(imageUri));
                        mIv_my_flower_1.setImageBitmap(bitmap);
                    } catch (FileNotFoundException e) {
                        e.printStackTrace();
                    }
                }
                break;
            default:
                break;
        }
    }

}
