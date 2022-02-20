package com.example.task1_service1.model;

import lombok.Builder;
import lombok.Data;

@Data
public class CityModel {
    private String name;
    private String country_code;
    private int population;

    public CityModel(){}
}
