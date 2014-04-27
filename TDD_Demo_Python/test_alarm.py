# -*- coding: iso-8859-15 -*-

import unittest
from mock import MagicMock
from alarm import Alarm
from sensor import Sensor


"""
Hälytysmoduulin Alarm testaus.
 * Käytetään test doublea, ts. aito Sensor on korvattu omalla Stub
   objektilla,koska todellinen sensoridata halutuilla testiarvoilla
   olisi hankala saada.
 * test_check_temp_ok_with_mock-metodi käyttää pythonin MagicMockia
   jolla voidaan Sensori "mokkata" uudeksi testi sensoriksi.
   Mock objektin hyöty omaan stubiin on, että se toteuttaa täysin saman
   interfacen kuin alkuperäinen objekti eli Sensor objekti.
   MagicMock ei ole valmiina pythonissa. Sen voi asentaa pip install mock
 * unittestit ajetaan komennolla:  python -m unittest test_alarm
 * Fake Objekteja (Fakes) tässä ei käydä läpi. Niillä saa resurssit
   feikattua jotta testistä tulee nopeampi ja riippumaton resursseista.
   esim. tietokanta, tiedosto, web service, web server...

 Summary:
  * Stub palauttaa kovakoodatun vastaukset testille
  * Fake on todellinen implementaatio jolla korvataan resursseja testissä
  * Mock on Stub jota käytetään interaktioiden testaamiseen
  * Test Spy mmahdollistaa toiminnallisuuden tarkastelun jälkikäteen
  * Dummy objektia käytetään kun interface vaatii argumentteja

Unit testauksen tarkoitus:
 * Auttaa ymmärtämään mitä tehdään
 * Ohjaa parempaan suunnitteluun ja arkkitehtuuriin
 * Arkkitehtuurista tulee sietokykyisempi muutoksille (Regression Protection)
 * Dokumentoi "unitit"
"""


class AlarmTest(unittest.TestCase):

    def test_alarm_is_off_by_default(self):
        alarm = Alarm()
        self.assertFalse(alarm.is_alarm_on)

    def test_check_too_low_temp_sounds_alarm(self):
        alarm = Alarm(sensor=TestSensor(2))  # arrange
        alarm.check()                        # act
        self.assertTrue(alarm.is_alarm_on)   # assert

    def test_check_too_high_temp_sounds_alarm(self):
        alarm = Alarm(sensor=TestSensor(32))
        alarm.check()
        self.assertTrue(alarm.is_alarm_on)

    def test_check_normal_temp_doesnt_sounds_alarm(self):
        alarm = Alarm(sensor=TestSensor(20))
        alarm.check()
        self.assertFalse(alarm.is_alarm_on)

    def test_check_temp_ok_with_mock(self):
        test_sensor = MagicMock(Sensor)
        test_sensor.sample_temperature.return_value = 20
        alarm = Alarm(sensor=test_sensor)
        alarm.check()
        self.assertFalse(alarm.is_alarm_on)


class TestSensor():
    def __init__(self, temp):
        self.temp = temp

    def sample_temperature(self):
        return self.temp
