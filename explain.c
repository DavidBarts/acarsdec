/*
 * Explain the various ACARS label types.
 * Sources:
 * http://www.cosmic.com.au/acarsanalyser/v3/DataRes/MsgLabels.htm
 * http://www.universal-radio.com/catalog/decoders/acars.pdf
 *
 *  Copyright (c) 2015 David Barts
 *
 *   This code is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct kv {
    char *key, *value;
};

char GeneralLab[] = "General response, demand mode; no information to transmit";
char AirlineLab[] = "Airline defined message";

struct kv explanations[] = {
    { "_", GeneralLab },
    { "_d", GeneralLab },
    { "_\x7f", GeneralLab },
    { "_j", "No info to transmit; polled mode" },
    { "00", "Emergency situation report" },
    { "2S", "Weather request" },
    { "2U", "Weather" },
    { "4M", "Cargo information" },
    { "51", "Ground GMT request/response" },
    { "52", "Ground UTC request/response" },
    { "54", "Aircrew initiated voice contact request" },
    { "57", "Alternate aircrew initiated position report" },
    { "5D", "ATIS request" },
    { "5P", "Temporary suspension of ACARS" },
    { "5R", "Aircraft initiated position report" },
    { "5U", "Weather request" },
    { "5Y", "Revision to previous ETA" },
    { "5Z", "Airline designated downlink" },
    { "7A", "Aircraft initiated engine data" },
    { "7B", "Aircraft initiated miscellaneous message" },
    { "80", "Aircraft addressed downlink 0" },
    { "81", "Aircraft addressed downlink 1" },
    { "82", "Aircraft addressed downlink 2" },
    { "83", "Aircraft addressed downlink 3" },
    { "84", "Aircraft addressed downlink 4" },
    { "85", "Aircraft addressed downlink 5" },
    { "86", "Aircraft addressed downlink 6" },
    { "87", "Aircraft addressed downlink 7" },
    { "88", "Aircraft addressed downlink 8" },
    { "89", "Aircraft addressed downlink 9" },
    { "8~", "Aircraft addressed downlink 10" },
    { "A1", "Deliver oceanic clearance" },
    { "A2", "Deliver departure clearance" },
    { "A4", "Acknowledge PDC" },
    { "A5", "Request position report" },
    { "A6", "Request ADS report" },
    { "A7", "Forward free text to aircraft" },
    { "A8", "Deliver departure slot" },
    { "A9", "Deliver ATIS information" },
    { "A0", "ATIS Facilities notification" },
    { "AA", "ATC Communications" },
    { "AB", "Terminal Weather Information for Pilots (TWIP)" },
    { "AC", "Pushback clearance" },
    { "AD", "Expected taxi clearance" },
    { "AE", "Unassigned" },
    { "AF", "CPC Command Response" },
    { "AG", "Unassigned" },
    { "B1", "Request oceanic clearance" },
    { "B2", "Request oceanic readback" },
    { "B3", "Request departure clearance" },
    { "B4", "Acknowledge departure clearance" },
    { "B5", "Provide position report" },
    { "B6", "Provide ADS report" },
    { "B7", "Forward free text to ATS" },
    { "B8", "Request departure slot" },
    { "B9", "Request ATIS information" },
    { "B0", "ATS Facility Notification (AFN)" },
    { "BA", "ATC communications" },
    { "BB", "Terminal Weather Information for Pilots (TWIP)" },
    { "BC", "Pushback clearance request" },
    { "BD", "Expected taxi clearance request" },
    { "BE", "CPC log-on/log-off request" },
    { "BF", "CPC WILCO/unassigned BLE response" },
    { "BG", "Unassigned" },
    { "C0", "Uplink message to all cockpit printers" },
    { "C1", "Uplink message to printer #1" },
    { "C2", "Uplink message to printer #2" },
    { "C3", "Uplink message to printer #3" },
    { "C4", "Uplink message to printer #4" },
    { "C5", "Uplink message to printer #5" },
    { "C6", "Uplink message to printer #6" },
    { "C7", "Uplink message to printer #7" },
    { "C8", "Uplink message to printer #8" },
    { "C9", "Uplink message to printer #9" },
    { "CA", "Printer status = error" },
    { "CB", "Printer status = busy" },
    { "CC", "Printer status = local" },
    { "CD", "Printer status = no paper" },
    { "CE", "Printer status = buffer overrun" },
    { "CF", "Printer status = reserved" },
    { "EI", "Internet e-mail message" },
    { "F3", "Dedicated transceiver advisory" },
    { "H1", "Message to/from terminal" },
    { "H2", "Meteorological report" },
    { "H3", "Icing report" },
    { "HX", "Undelivered uplink report" },
    { "M1", "IATA Departure message" },
    { "M2", "IATA Arrival message" },
    { "M3", "IATA Return to ramp message" },
    { "M4", "IATA Return from airborne message" },
    { "Q0", "ACARS link test" },
    { "Q1", "ETA Departure/arrival reports" },
    { "Q2", "ETA reports" },
    { "Q3", "Clock update" },
    { "Q4", "Voice circuit busy (response to 54)" },
    { "Q5", "Unable to process uplinked messages" },
    { "Q6", "Voice-to-ACARS change-over" },
    { "Q7", "Delay message" },
    { "QA", "Out/fuel report" },
    { "QB", "Off report" },
    { "QC", "On report" },
    { "QD", "In/fuel report" },
    { "QE", "Out/fuel destination report" },
    { "QF", "Off/destination report" },
    { "QG", "Out/return in report" },
    { "QH", "Out report" },
    { "QK", "Landing report" },
    { "QL", "Arrival report" },
    { "QM", "Arrival information report" },
    { "QN", "Diversion report" },
    { "QP", "OUT report" },
    { "QQ", "OFF report" },
    { "QR", "ON report" },
    { "QS", "IN report" },
    { "QT", "OUT/return IN report" },
    { "QX", "Intercept" },
    { "S1", "Network statistics request/response" },
    { "S2", "VHF performance report request" },
    { "S3", "LRU configuration request/response" },
    { "SA", "Media advisory" },
    { "SQ", "Squitter message" },
    { "X1", "Service provider defined DSP" },
    { "RA", "Command aircraft term. to transmit data" },
    { "RB", "Response of aircraft terminal to RA message" },
    { ":;", "Command aircraft xcvr to change frequency" },
    { "10", AirlineLab },
    { "11", AirlineLab },
    { "12", AirlineLab },
    { "13", AirlineLab },
    { "14", AirlineLab },
    { "15", AirlineLab },
    { "16", AirlineLab },
    { "17", AirlineLab },
    { "18", AirlineLab },
    { "19", AirlineLab },
    { "20", AirlineLab },
    { "21", AirlineLab },
    { "22", AirlineLab },
    { "23", AirlineLab },
    { "24", AirlineLab },
    { "25", AirlineLab },
    { "26", AirlineLab },
    { "27", AirlineLab },
    { "28", AirlineLab },
    { "29", AirlineLab },
    { "30", AirlineLab },
    { "31", AirlineLab },
    { "32", AirlineLab },
    { "33", AirlineLab },
    { "34", AirlineLab },
    { "35", AirlineLab },
    { "36", AirlineLab },
    { "37", AirlineLab },
    { "38", AirlineLab },
    { "39", AirlineLab },
    { "40", AirlineLab },
    { "41", AirlineLab },
    { "42", AirlineLab },
    { "43", AirlineLab },
    { "44", AirlineLab },
    { "45", AirlineLab },
    { "46", AirlineLab },
    { "47", AirlineLab },
    { "48", AirlineLab },
    { "49", AirlineLab },
    { "4~", AirlineLab }
};

int _lcompare(const struct kv *l1, const struct kv *l2)
{
    return strcmp(l1->key, l2->key);
}

char *explain(char *lstr)
{
    struct kv key, *expl;
    static bool unsorted = true;

    if (unsorted) {
        mergesort(
            &explanations[0],
            sizeof(explanations) / sizeof(explanations[0]),
            sizeof(explanations[0]),
            (int (*)(const void *, const void *)) _lcompare);
        unsorted = false;
    }

    key.key = lstr;
    expl = bsearch(
        &key,
        &explanations[0],
        sizeof(explanations) / sizeof(key),
        sizeof(key),
        (int (*)(const void *, const void *)) _lcompare);
    return expl == NULL ? "Unknown" : expl->value;
}

char UnknownH1[] = "Unknown";
char AirlineH1[] = "Airline defined";
char TerminalH1[] = "Cabin terminal";

struct kv h1_expl[] = {
    { "CF", "Central fault data indicator" },
    { "DF", "Flight data recorder" },
    { "EC", "Engine display system" },
    { "EI", "Engine report" },
    { "H1", "HF data radio #1" },
    { "H2", "HF data radio #2" },
    { "HD", "HF data radio" },
    { "M1", "Flight management computer #1" },
    { "M2", "Flight management computer #2" },
    { "M3", "Flight management computer #3" },
    { "MD", "Flight management computer" },
    { "PS", "Keyboard/display unit" },
    { "S1", "Satellite data unit #1" },
    { "S2", "Satellite data unit #2" },
    { "SD", "Satellite data unit" },
    { "T0", TerminalH1 },
    { "T1", TerminalH1 },
    { "T2", TerminalH1 },
    { "T3", TerminalH1 },
    { "T4", TerminalH1 },
    { "T5", TerminalH1 },
    { "T6", TerminalH1 },
    { "T7", TerminalH1 },
    { "T8", TerminalH1 },
    { "WO", "Weather observation" }
};

char *explain_h1(char *mbody)
{
    struct kv key, *expl;
    static bool unsorted = true;
    char keybuf[3];
    static char ret[256];
    char *rret, *mstart;
    int skipped;

    if (unsorted) {
        mergesort(
            &h1_expl[0],
            sizeof(h1_expl) / sizeof(h1_expl[0]),
            sizeof(h1_expl[0]),
            (int (*)(const void *, const void *)) _lcompare);
        unsorted = false;
    }

    for (mstart=mbody, skipped=0; *mstart && skipped < 4; mstart++, skipped++) {
        if (*mstart == '#')
            break;
    }

    if (strlen(mstart) < 3 || mstart[0] != '#')
        return UnknownH1;

    keybuf[0] = mstart[1];
    keybuf[1] = mstart[2];
    keybuf[2] = '\0';
    key.key = keybuf;

    if (keybuf[0] >= '0' && keybuf[0] <= '9') {
        snprintf(ret, 256, "%s (%s)", keybuf, AirlineH1);
        return ret;
    }

    expl = bsearch(
        &key,
        &h1_expl[0],
        sizeof(h1_expl) / sizeof(key),
        sizeof(key),
        (int (*)(const void *, const void *)) _lcompare);
    rret = expl == NULL ? UnknownH1 : expl->value;

    snprintf(ret, 256, "%s (%s)", keybuf, rret);
    return ret;
}
