package com.hzau.xuwei.flowermanager.domain;

import cn.bmob.v3.BmobObject;

/**
 * @version $Rev$
 * @auther Administrator
 * @des ${TODO}
 * @updataAuthor $Author$
 * @updateDes ${TODO}
 */

public class BmobFlowers extends BmobObject{
    private String flowerID;  //花卉ID
    private String name;  //花卉名称
    private String monitor_id;  //监测系统ID
    private String describe;  //花卉描述
    private Number humidity=0; //湿度
    private Number temperature=0; //温度
    private Number co2=0; //CO2浓度
    private Number bulk=0;  //浇水量
    private boolean flag_watering=false;  //浇水标志位

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getMonitor_id() {
        return monitor_id;
    }

    public void setMonitor_id(String monitor_id) {
        this.monitor_id = monitor_id;
    }

    public String getDescribe() {
        return describe;
    }

    public void setDescribe(String describe) {
        this.describe = describe;
    }

    public Number getHumidity() {
        return humidity;
    }

    public void setHumidity(Number humidity) {
        this.humidity = humidity;
    }

    public Number getTemperature() {
        return temperature;
    }

    public void setTemperature(Number tempreture) {
        this.temperature = tempreture;
    }

    public Number getCo2() {
        return co2;
    }

    public void setCo2(Number co2) {
        this.co2 = co2;
    }

    public Number getBulk() {
        return bulk;
    }

    public void setBulk(Number bulk) {
        this.bulk = bulk;
    }

    public boolean getFlag_watering() {
        return flag_watering;
    }

    public void setFlag_watering(boolean flag_watering) {
        this.flag_watering = flag_watering;
    }
}
