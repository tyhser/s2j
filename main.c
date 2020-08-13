/*
 * This file is part of the struct2json Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: demo for this library.
 * Created on: 2015-10-14
 */

#include "s2j.h"
#include <stdint.h>
#include <stdio.h>

typedef struct {
    char name[16];
} Hometown;

typedef struct {
    uint8_t id;
    double weight;
    uint8_t score[8];
    char name[10];
    Hometown hometown;
} Student;

/**
 * Student JSON object to structure object
 *
 * @param json_obj JSON object
 *
 * @return structure object
 */
static void *json_to_struct(cJSON* json_obj) {
    /* create Student structure object */
    s2j_create_struct_obj(struct_student, Student);

    /* deserialize data to Student structure object. */
    s2j_struct_get_basic_element(struct_student, json_obj, int, id);
#if 1
    s2j_struct_get_array_element(struct_student, json_obj, int, score);
    s2j_struct_get_basic_element(struct_student, json_obj, string, name);
    s2j_struct_get_basic_element(struct_student, json_obj, double, weight);
#else // another xxx_ex api, add default value and more secure
    s2j_struct_get_array_element_ex(struct_student, json_obj, int, score, 8, 0);
    s2j_struct_get_basic_element_ex(struct_student, json_obj, string, name, "John");
    s2j_struct_get_basic_element_ex(struct_student, json_obj, double, weight, 0);
#endif

    /* deserialize data to Student.Hometown structure object. */
    s2j_struct_get_struct_element(struct_hometown, struct_student, json_hometown, json_obj, Hometown, hometown);
    s2j_struct_get_basic_element(struct_hometown, json_hometown, string, name);

    /* return Student structure object pointer */
    return struct_student;
}

/**
 * Student structure object to JSON object
 *
 * @param struct_obj structure object
 *
 * @param JSON object
 */
static cJSON *struct_to_json(void* struct_obj) {
    Student *struct_student = (Student *)struct_obj;

    /* create Student JSON object */
    s2j_create_json_obj(json_student);

    /* serialize data to Student JSON object. */
    s2j_json_set_basic_element(json_student, struct_student, int, id);
    s2j_json_set_basic_element(json_student, struct_student, double, weight);
    s2j_json_set_array_element(json_student, struct_student, int, score, 8);
    s2j_json_set_basic_element(json_student, struct_student, string, name);

    /* serialize data to Student.Hometown JSON object. */
    s2j_json_set_struct_element(json_hometown, json_student, struct_hometown, struct_student, Hometown, hometown);
    s2j_json_set_basic_element(json_hometown, struct_hometown, string, name);

    /* return Student JSON object pointer */
    return json_student;
}

char *json = "{\"deviceName\":\"FP2SH_1\",\"driveConfig\":{\"bau\":192000,\"databit\":8,\"stopbit\":1,\"parity\":\"Odd\",\"station\":238},\" points\":[{\"path\":\"fp01\",\"address\":\"R0\",\"type\":\"uint32\",\"cycle\":1000},{\"path\":\"fp02\",\"address\":\"Y0\",\"type\":\"bool\",\"cycle\":5000},{\"path\":\"fp03\",\"addre ss\":\"X1\",\"type\":\"bool\",\"cycle\":5000}]}";

typedef struct {
    int baud;
    int databit;
    int stopbit;
    int parity;
    int station;

} device_cfg_t;

typedef struct {
    char deviceName[32];
    device_cfg_t driveConfig;
} device_t;

typedef struct {
    char path[32];
    char address[32];
    char type[32];
    int cycle;
} point_t;

static void *parse_to_struct(cJSON* json_obj) {
    /* create Student structure object */
    s2j_create_struct_obj(device, device_t);

    /* deserialize data to Student structure object. */
    s2j_struct_get_basic_element(device, json_obj, string, deviceName);

    s2j_struct_get_struct_element(config, device, json_dev_cfg, json_obj, device_cfg_t, driveConfig);
    s2j_struct_get_basic_element_ex(config, json_dev_cfg, int, baud, 115200);
    s2j_struct_get_basic_element(config, json_dev_cfg, int, databit);
    s2j_struct_get_basic_element(config, json_dev_cfg, int, stopbit);
    s2j_struct_get_basic_element(config, json_dev_cfg, int, parity);
    s2j_struct_get_basic_element(config, json_dev_cfg, int, station);

    return device;
}

int main(void) {

    cJSON *json_obj = cJSON_Parse(json);
    parse_to_struct(json_obj);



    return 0;
}
