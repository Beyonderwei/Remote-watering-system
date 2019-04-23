package com.hzau.xuwei.flowermanager.domain;

/**
 * @version $Rev$
 * @auther Administrator
 * @des ${TODO}
 * @updataAuthor $Author$
 * @updateDes ${TODO}
 */

public class Flower {
    private String name;
    private String monitor_id;
    private String describe;

    public String getName() {
        return name;
    }

    public String getMonitor_id() {
        return monitor_id;
    }

    public String getDescribe() {
        return describe;
    }

    public Flower(String f_name, String f_monitor_id, String f_describe) {
        name = f_name;
        monitor_id = f_monitor_id;
        describe = f_describe;
    }



}
