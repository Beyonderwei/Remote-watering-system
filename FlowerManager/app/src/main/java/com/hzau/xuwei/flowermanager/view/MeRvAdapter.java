package com.hzau.xuwei.flowermanager.view;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.hzau.xuwei.flowermanager.R;

import java.util.Calendar;

/**
 * @version $Rev$
 * @auther Administrator
 * @des ${用给“我” 界面 RecycleView 的适配}
 * @updataAuthor $Author$
 * @updateDes ${TODO}
 */

public class MeRvAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder>{

    private Context mContext;

    private OnItemClickListener mListener;

    public MeRvAdapter(Context context ,OnItemClickListener listener) {
        this.mContext = context;
        this.mListener=listener;
    }


    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        //传入的View即为每一个Item长什么样子的View
        //根据ViewType的类型来设置每个Item长什么样
        //@TODO 根据case的值 显示不同的layout
        switch (viewType) {
            case 0:return new LinearViewHolder_0(LayoutInflater.from(mContext).inflate(R.layout.activity_me_view_item_0, parent, false));
            default:return new LinearViewHolder_1(LayoutInflater.from(mContext).inflate(R.layout.activity_me_view_item_0, parent, false));
        }
    }

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder holder, final int position) {

        //通过holder去设置内容
        if (getItemViewType(position)==0  || getItemViewType(position)==2||getItemViewType(position)==4){
            //((LinearViewHolder_1)holder).mTextView.setText("瞌睡遇上枕头"); //这里可以设置其他的
        }
        else {
            //((LinearViewHolder_1)holder).mTextView.setText("你的坚持终将美好");
        }
        //设置点击事件
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Toast.makeText(mContext, "我是第" + position + "个List", Toast.LENGTH_SHORT).show();
                mListener.onClick(position);
            }
        });


        //@TODO 同样这里可以实现每一个Item的OnLongClickListner 同样需要在上面Adapter的构造方法中传入这个接口的索引
        //        holder.itemView.setOnLongClickListener(new View.OnLongClickListener(){
        //
        //            @Override
        //            public boolean onLongClick(View view) {
        //                return false;
        //            }
        //        });
    }

    /**
     * 这个方法用来设置每一个Item的样式
     * @param position
     * @return
     */
    @Override
    public int getItemViewType(int position) {
        switch (position) {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 3;
            case 4:
                return 4;
            case 5:
                return 5;
            default:return 0; //这里的返回值0是乱写的  不写会报错误 索性就都让他返回第一中状态的Item
        }
    }


    @Override
    public int getItemCount() {
        //设置列表的长度 根据返回值的数决定了列表的长度
        return 2;  //这里返回30个 暂时写死   正常是创建一个列表数据
    }


    /**
     * 两种不同的ViewHolder
     */
    //用给通知界面

    class LinearViewHolder_0 extends RecyclerView.ViewHolder {

        //声明布局中的控件
        private TextView mTv_me_date_time;
        private int year, month, day, hour, minute;

        public LinearViewHolder_0(View itemView) {
            super(itemView);
            //因为这个textVIew在itemView这个布局当中  所以用它来fdvc
            mTv_me_date_time = (TextView) itemView.findViewById(R.id.tv_me_date_time);
            Calendar c = Calendar.getInstance();
            //取得系统日期:
            year = c.get(Calendar.YEAR);
            month = c.get(Calendar.MONTH);
            day = c.get(Calendar.DAY_OF_MONTH);
            //取得系统时间：
            hour = c.get(Calendar.HOUR_OF_DAY);
            minute = c.get(Calendar.MINUTE);

            String s = year + "-" + month + "-" + day + "-" + hour + "-" + minute;
            System.out.println("当前时间："+s);
            mTv_me_date_time.setText(s);
        }
    }


    class LinearViewHolder_1 extends RecyclerView.ViewHolder {

        //声明布局中的控件
        //private TextView mTextView;

        public LinearViewHolder_1(View itemView) {
            super(itemView);
            //因为这个textVIew在itemView这个布局当中  所以用它来fdvc
            //mTextView = (TextView) itemView.findViewById(R.id.tv_inform_title);

        }
    }

    //定义一个接口 使得可以在MeViewActivity里面或者其他Activity中调用RecyclerView的每一个Item的点击事件
    public interface OnItemClickListener{
        void onClick(int pos);
    }
}
