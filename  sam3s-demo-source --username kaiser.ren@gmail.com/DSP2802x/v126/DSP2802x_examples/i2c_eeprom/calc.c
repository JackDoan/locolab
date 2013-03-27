/*
 * calc.c
 *
 *  Created on: 2012-11-26
 *      Author: cui
 */
#include <math.h>
#include <stdio.h>
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "ad5933.h"
#include "Example_2802xI2C_eeprom/com.h"
#include "IQmathLib.h"


const double mag_ref[AD5933_BOARD_CNT_ICMT] = {
		82.1021905,
		81.46607672,
		81.71814055,
		81.40702933,
		82.43416499,
		82.50284468,
		82.42916572,
		81.51770473,
		81.21807881,
		81.11327282,
		81.10328592,
		80.8553484,
		81.61442029,
		82.4829716,
		83.2641998,
		83.76461058,
		83.38422118,
		84.54697695,
		84.98804226,
		84.88940562,
		82.6599388,
		84.00134889,
		83.07014991,
		79.99907653,
		82.67058499,
		82.96920836,
		83.30688403,
		83.77212617,
		83.91650777,
		83.64738555,
		83.39329691,
		82.53110913,
		82.36293242,
		83.10438703,
		83.60194608,
		83.95944751,
		83.98636752,
		83.88431868,
		83.03357503,
		81.22997769,
		82.08812822,
		82.67597482,
		82.75193112,
		82.6554983,
		82.12779266,
		81.5860335,
		80.96766212,
		80.38018735,
		79.85501584,
		79.63173723,
		79.53670317,
		79.52513645,
		79.37927434,
		79.1785649,
		78.91737473,
		78.36917353,
		76.77244175,
		74.79930663,
		76.77659368,
		78.30220058,
		78.64677495,
		78.04422811,
		75.69489383,
		73.91358026,
		74.83960626,
		75.58746431,
		76.04722701,
		76.13508695,
		75.88715809,
		76.00326512,
		75.97481874,
		75.74470112,
		75.51233771,
		75.41325168,
		75.41797963,
		75.60259133,
		75.93448804,
		76.09666001,
		75.68857591,
		76.36116605,
		76.53914248,
		76.59871088,
		76.41280536,
		75.86350043,
		75.50257711,
		75.11504929,
		74.673983,
		74.15369073,
		73.8237691,
		73.16639194,
		72.44414801,
		71.57694486,
		70.94753508,
		70.87766987,
		70.69672055,
		70.31730508,
		70.12343968,
		69.44163607,
		68.85504164,
		68.92960328,
		69.20688178,
		69.45697829,
		69.85434617,
		69.98331052,
		70.13333174,
		70.37756424,
		70.65470966,
		70.88737909,
		71.1936866,
		71.26140884,
		71.43531359,
		71.43061199,
		71.10659232,
		70.61937252,
		70.69387769,
		70.94821914,
		71.02167918,
		70.76488695,
		70.61477538,
		70.44881131,
		70.25544965,
		70.23545598,
		70.38224727,
		70.44336519,
		70.44229895,
		70.50598631,
		70.50149814,
		70.645736,
		70.93502625,
		71.58471117,
		72.56032374,
		73.66870413,
		74.56599404,
		75.34572318,
		75.9577745,
		76.69398975,
		77.33522163,
		77.67227326,
		77.60349807,
		77.30508353,
		76.85428895,
		76.42471387,
		76.03078418,
		75.62675655,
		75.24766136,
		74.89495766,
		74.58877434,
		74.35890436,
		74.19743805,
		74.04988976,
		73.91824594,
		73.82882017,
		73.76662691,
		73.77429355,
		73.69831892,
		73.48080466,
		73.05036265,
		72.35743464,
		71.41978717,
		70.22694602,
		69.19805701,
		68.80474393,
		68.77064594,
		68.57210916,
		68.20366604,
		68.07379666,
		67.72700013,
		67.5356141,
		67.8545491,
		68.33868856,
		68.6226135,
		68.68554041,
		68.57282216,
		68.28675782,
		67.98382508,
		67.58841217,
		67.19475185,
		66.81564432,
		66.47290364,
		66.12502059,
		65.93362379,
		65.73138556,
		65.58872512,
		65.60107401,
		65.62334579,
		65.61490469,
		65.57849078,
		65.55005337,
		65.57616755,
		65.45820806,
		65.49761104,
		65.52122213,
		65.49640502,
		65.4229846,
		65.334479,
		65.04142162,
		64.64369713,
		64.12868447,
		63.95865606,
		63.88389477,
		64.07208102,
		64.48451645,
		64.70578569,
		64.73939663,
		64.54868099,
		64.30900188,
		63.86579296,
		63.43420268,
		62.87503186,
		62.52682893,
		62.34480224,
		62.10891219,
		61.97495035,
		61.71166168,
		61.4922503,
		61.22586113,
		60.93792647,
		60.74106057,
		60.41422451,
		60.24783919,
		60.05452836,
		59.46571564,
		59.15722229,
		60.22063571,
		60.90751484,
		61.56217771,
		62.16706128,
		62.80396363,
		63.4149981,
		64.08494973,
		64.7282358,
		65.37540053,
		65.99992053,
		66.58393863,
		67.10667042,
		67.57931954,
		67.95873625,
		68.28608521,
		68.49011726,
		68.66282303,
		68.71018987,
		68.72667605,
		68.69143901,
		68.58044671,
		68.49614862,
		68.34002647,
		68.1618774,
		67.99492708,
		67.8101296,
		67.63592422,
		67.46201853,
		67.22541733,
		66.95577048,
		66.5674574,
		66.40458876,
		66.51493227,
		66.98032648,
		67.30455356,
		67.62245435,
		67.88918953,
		68.09020406,
		68.1421757,
		68.20056432,
		68.00000915,
		67.72712599,
		67.26085683,
		66.67785999,
		66.09165541,
		65.39500443,
		64.56748544,
		63.4288355,
		61.85221225,
		62.08828871,
		63.3154622,
		63.681397,
		64.00593898,
		64.04824429,
		63.98201138,
		63.80975974,
		63.64927221,
		63.47194443,
		63.3200005,
		63.11020208,
		62.87281923,
		62.5867679,
		62.22082644,
		61.90950349,
		61.49997831,
		61.05394295,
		60.62997177,
		60.13163746,
		59.59107081,
		59.1893892,
		59.08639244,
		58.97898937,
		58.90606101,
		58.81008033,
		58.62830016,
		58.5654685,
		58.5546507,
		58.573328,
		58.71884694,
		58.81109223,
		58.83788704,
		59.03262677,
		59.24545743,
		59.37309857,
		59.52163634,
		59.62701164,
		59.77069166,
		59.96740971,
		60.21221104,
		60.4921516,
		60.792343,
		61.12581176,
		61.44519195,
		61.71454696,
		61.96205878,
		62.26529565,
		62.48372843,
		62.69224622,
		62.81852738,
		62.71653657,
		62.79892427,
		62.50377656,
		62.10913008,
		61.88774287,
		62.73051596,
		63.30187659,
		63.67759484,
		63.93181191,
		64.12880525,
		64.27756283,
		64.22763159,
		64.1611215,
		64.1386468,
		64.14096173,
		64.21439773,
		64.30342851,
		64.39501815,
		64.41663891,
		64.40854679,
		64.34957764,
		64.20809892,
		63.97608199,
		63.75031773,
		63.85072042,
		64.26556013,
		64.59854109,
		64.84934268,
		65.07376158,
		65.25888573,
		65.34954766,
		65.40880863,
		65.46984935,
		65.52188314,
		65.54522946,
		65.52486494,
		65.52890523,
		65.53267301,
		65.4534992,
		65.4117571,
		65.3390377,
		65.23104292,
		65.1171123,
		65.02069638,
		64.90396232,
		64.78365253,
		64.64033025,
		64.5053406,
		64.33173789,
		64.14528185,
		63.92558895,
		63.68082311,
		63.43504683,
		63.12573753,
		62.7915042,
		62.40227362,
		61.98757182,
		61.50054979,
		61.00486778,
		60.45308832,
		59.83985643,
		59.21269162,
		58.60009283,
		58.03305118,
		57.38909277,
		56.91135715,
		56.46465539,
		56.25994078,
		56.03604711,
		55.95551446,
		55.87552765,
		56.10751476,
		56.42840503,
		56.6294875,
		56.89754948,
		57.01677802,
		57.07452933,
		57.15685287,
		57.36778119,
		57.65256606,
		57.94592275,
		58.23486978,
		58.47041632,
		58.75722723,
		58.92034998,
		59.09110415,
		59.09794066,
		59.12588978,
		59.12906417,
		59.08256087,
		59.0271708,
		58.89289484,
		58.70660691,
		58.60094528,
		58.3631782,
		58.10506591,
		57.92155998,
		57.59079192,
		57.18352754,
		56.91896253,
		56.34871019,
		55.42160109,
		53.9694073,
		55.15322761,
		55.6803521,
		55.75112737,
		55.93926292,
		55.95317408,
		55.86263613,
		55.85260626,
		55.68096409,
		55.49700798,
		55.31954519,
		55.0153404,
		54.80831929,
		54.65289776,
		54.9321962,
		55.34878017,
		55.66930786,
		55.81572218,
		55.94069427,
		56.02660338,
		56.04744314,
		56.12907079,
		56.03997115,
		55.93942371,
		55.75560332,
		55.63290696,
		55.36997144,
		55.24624448,
		55.0222637,
		54.91248589,
		54.87912697,
		55.10706753,
		55.26524434,
		55.4306292,
		55.69739849,
		55.89455348,
		56.15649955,
		56.37580063,
		56.46579137,
		56.54471685,
		56.62643444,
		56.79078134,
		56.8176813,
		56.95829976,
		57.12393426,
		57.29258943,
		57.5187212,
		57.72088503,
		57.948279,
		58.18736125,
		58.41939285,
		58.62960491,
		58.81114035,
		58.98188337,
		59.09342062,
		59.20290249,
		59.26321261,
		59.25450031,
		59.26475288,
		59.20975466,
		59.19701655,
		59.08710767,
		59.02317869,
		58.92132402,
		58.80183887,
		58.67124509,
		58.52130122,
		58.37856023,
		58.19170126,
		58.06062367,
		57.8963752,
		57.7243161,
		57.53726059,
		57.40386978,
		57.31125831,
		57.26766623,
		57.39174128,
		57.56197526,
		57.86634907,
		58.19514411,
		58.55447537,
		58.88237027,
		59.16752354,
		59.39564334,
		59.55286846,
		59.69898897,
		59.78920228,
		//59.8344069
};

void modular_operate(void)
{

}

//eof
