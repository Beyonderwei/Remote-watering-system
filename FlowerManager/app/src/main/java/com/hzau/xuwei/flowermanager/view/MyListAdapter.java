package com.hzau.xuwei.flowermanager.view;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.hzau.xuwei.flowermanager.R;
import com.hzau.xuwei.flowermanager.domain.Flower;
import com.hzau.xuwei.flowermanager.service.FlowerInfoDao;

import java.util.ArrayList;

/**
 * @version $Rev$
 * @auther Administrator
 * @des ${用给主界面的ListView}
 * @updataAuthor $Author$
 * @updateDes ${TODO}
 */

public class MyListAdapter extends BaseAdapter {

    private Context mContext;
    private LayoutInflater mLayoutInflater;
    public int mItemNumber = 0;
    private FlowerInfoDao mFlowerInfoDao;


    public MyListAdapter(Context context) {
        this.mContext = context;
        mLayoutInflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        //new 一个FlowerInfoDao 读取数据库数据
        mFlowerInfoDao = new FlowerInfoDao(mContext);
        int item_numbwer = mFlowerInfoDao.getCount();
        return item_numbwer;  //这里从数据库获取个数显示
    }

    @Override
    public Object getItem(int i) {
        return null;
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    static class ViewHolder {
        public ImageView imageView;
        public TextView textView_name, textView_desc, textView_monitor_id;
    }


    //列表的每一行长什么样
    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        ViewHolder holder = null;
        if (view == null) {
            view = mLayoutInflater.inflate(R.layout.activity_list_view__main, null);
            holder = new ViewHolder();
            holder.imageView = (ImageView) view.findViewById(R.id.iv_flower);
            holder.textView_name = (TextView) view.findViewById(R.id.tv_name);
            holder.textView_monitor_id = (TextView) view.findViewById(R.id.monitor_id);
            holder.textView_desc = (TextView) view.findViewById(R.id.tv_desc);
            view.setTag(holder);
        } else {
            holder = (ViewHolder) view.getTag();
        }

        //用list存储数据库数据 显示在每一个Item上面
        ArrayList<Flower> flowers = new  ArrayList<>();
        //new 一个FlowerInfoDao 读取数据库数据
        mFlowerInfoDao = new FlowerInfoDao(mContext);
        flowers = mFlowerInfoDao.queryAll();  //将数据存放在array list中
        holder.textView_name.setText(flowers.get(i).getName());
        holder.textView_monitor_id.setText(flowers.get(i).getMonitor_id());
        holder.textView_desc.setText(flowers.get(i).getDescribe());
        Glide.with(mContext).load("https://ss2.bdstatic.com/70cFvnSh_Q1YnxGkpoWK1HF6hhy/it/u=899397896,788282742&fm=27&gp=0.jpg").into(holder.imageView);
        return view;
    }
}
