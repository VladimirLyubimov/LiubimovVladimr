package com.example.task1_service1.controller;

import com.example.task1_service1.model.CityModel;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.client.RestTemplate;

@RestController
public class RequestBrokerController {
    private static final Logger logger =  LoggerFactory.getLogger(RequestBrokerController.class);

    @GetMapping
    public CityModel[] makeRequest(@RequestParam String query){
        logger.info("Request accepted");
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject("http://localhost:8100?query=" + query.replace(' ', '+'), CityModel[].class);
    }
}
