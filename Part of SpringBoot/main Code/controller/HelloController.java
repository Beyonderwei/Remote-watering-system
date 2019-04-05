package com.hzauxw.springboot.controller;

import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Controller
public class HelloController {

    @Autowired
    JdbcTemplate jdbcTemplate;


    /*-------------------处理 APP 与后台的交互-----------------*/

    /**
     * 处理 APP 发送过来的 GET 请求 -> 查询花卉的所有信息返回给 APP
     *
     * @param flower_name
     * @return
     */
    @ResponseBody   //用于将数据写出去
    @GetMapping("/appQuery")   //这个方法用来处理query请求
    public List<Map<String, Object>> appGetResponse(@RequestParam String flower_name) {
        //这个字符串拼接的方法来实现sql语句中嵌套变量
        String querySql = "select * From flowers where name =" + "'" + flower_name + "'";
        List<Map<String, Object>> list = jdbcTemplate.queryForList(querySql);
        System.out.println(list);
        return list;
    }


    /**
     * 处理 APP POST 给服务器的数据 ->更新数据库中的浇水量 bulk  @TODO
     */


    @ResponseBody   //用于接收APP post 过来的数据
    @PostMapping("/appPost")   //这个方法用来处理App的post请求
    public void appPostResponse(@RequestBody String flower_info) throws JSONException {
        /*--更改花卉的浇水量--*/
        String mFlower_name;
        int mBulk;
        //1.解析post过来的数据
        JSONObject jsonObject = new JSONObject(flower_info);
        mFlower_name = jsonObject.getString("name");
        mBulk = jsonObject.getInt("bulk");

        //2.根据花卉名称和浇水量更新DB的数据
        String updateSql = "update flowers set bulk =" + "'" + mBulk + "'" + " WHERE name =" + "'" + mFlower_name + "'";    //@TODO
        jdbcTemplate.update(updateSql);
    }


    /*-----------------------处理 CC3200 与后台的交互-------------------*/

    /**
     * 处理CC3200 发送过来的 GET 请求 ->查询花卉的浇水量返回给CC3200  @TODO
     */
    @ResponseBody   //用于将数据写出去
    @GetMapping("/cc3200Query")   //这个方法用来处理query请求
    public Map<String, Object> cc3200GetResponse() {


        /*--直接查询四个花的浇水量--*/
        String querySql = "select monitor_id,SUM(bulk) From flowers GROUP BY monitor_id";
        String updateSql = "update flowers set bulk =0";

        List<Map<String, Object>> list = jdbcTemplate.queryForList(querySql);
        //查询完数据后再将浇水量更新为0
        jdbcTemplate.update(updateSql);

        Map<String, Object> map = new HashMap<>();
        map.put("flowers", list);
        System.out.println(list);
        return map;
    }


    /**
     * 处理CC3200 POST 给服务器的数据 ->更新花卉的状态信息 @TODO
     */

    @ResponseBody   //用于接收CC3200 post 过来的数据
    @PostMapping("/cc3200Post")   //这个方法用来处理CC3200Post请求
    public void CC3200PostResponse(@RequestBody String flower_info) throws JSONException {
        /*--更新花卉的状态信息--*/
        int light;
        int monitorID;
        float co2;
        float temperature;
        float humidity;
        System.out.println("post:" + flower_info);
        //1.解析post过来的数据
        JSONObject jsonObject = new JSONObject(flower_info);
        monitorID = jsonObject.getInt("monitorID");
        co2 = (float) jsonObject.getDouble("co2");
        temperature = (float) jsonObject.getDouble("temperature");
        humidity = (float) jsonObject.getDouble("humidity");
        light = jsonObject.getInt("light");

        //2.根据花卉监测系统ID更新数据库的数据
        String updateSql =
                "update flowers set co2 =" + "'" + co2 + "'" + "," +
                        "light =" + "'" + light + "'" + "," +
                        "temperature =" + "'" + temperature + "'" + "," +
                        "humidity =" + "'" + humidity + "'" +
                        " WHERE monitor_id =" + "'" + monitorID + "'";
        jdbcTemplate.update(updateSql);
    }

}
