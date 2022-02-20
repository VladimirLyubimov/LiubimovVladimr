package com.example.task1_service2.model;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class CityModel {
    private String name;
    private String country_code;
    private int population;
}
