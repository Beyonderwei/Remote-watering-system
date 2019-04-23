//package com.hzau.xuwei.flowermanager.service;
//
//import android.text.TextUtils;
//import android.util.Xml;
//
//import com.hzau.xuwei.flowermanager.domain.FlowerItem;
//
//import org.xmlpull.v1.XmlPullParser;
//
//import java.io.InputStream;
//import java.util.ArrayList;
//import java.util.List;
//
///**
// * 业务类 用来解析新闻的信息
// * @version $Rev$
// * @auther Administrator
// * @des ${TODO}
// * @updataAuthor $Author$
// * @updateDes ${TODO}
// */
//
//public class NewsInfoParser {
//    public static List<FlowerItem> getAllNewsInfo(InputStream is) throws Exception {
//        List<FlowerItem> newsItems =null;//新闻对象的集合
//        FlowerItem newsItem=null;//某一个新闻的实体
//        //1.获取XML文件的解析器
//        XmlPullParser parser = Xml.newPullParser();
//        //2.初始化xml文件解析器
//        parser.setInput(is,"utf-8");
//        //3.解析xml文件
//        int type = parser.getEventType();
//        while (type!=XmlPullParser.END_DOCUMENT){
//            switch (type){
//                case XmlPullParser.START_TAG:
//                    if ("channel".equals(parser.getName())){
//                        //说明解析到了最根部的标签节点
//                        newsItems=new ArrayList<>();
//                    }else if ("item".equals(parser.getName())){
//                        newsItem=new FlowerItem();
//                    }else if ("title".equals(parser.getName())){
//                        newsItem.setTitle(parser.nextText());
//                    }else if ("description".equals(parser.getName())){
//                        newsItem.setDesc(parser.nextText());
//                    }else if ("image".equals(parser.getName())){
//                        newsItem.setImagePath(parser.nextText());
//                    }else if ("type".equals(parser.getName())){
//                        newsItem.setType(parser.nextText());
//                    }else if ("comment".equals(parser.getName())){
//                        String countstr=parser.nextText();
//                        if (TextUtils.isDigitsOnly(countstr)){
//                            newsItem.setCommentCount(Integer.parseInt(countstr));
//                        }
//                    }
//                    break;
//                case XmlPullParser.END_TAG:
//                    //如果走到了一个item的标签 说明一个item的数据已经准备好了 要添加到集合当中
//                    if ("item".equals(parser.getName())){
//                        newsItems.add(newsItem);
//                    }
//                    break;
//            }
//            type=parser.next();
//        }
//
//        return newsItems;
//    }
//}
