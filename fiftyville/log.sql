-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- 28 Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. [contain 'bakery'; took place 10.15am]

SELECT * FROM interviews WHERE transcript LIKE '%bakery%' AND year = 2021 AND month = 7 AND day = 28;
-- 161	Ruth	2021	7	28	Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame. [look for carplate 1015 - 1025]

SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- 260	2021	7	28	10	16	exit	5P2BI95
-- 261	2021	7	28	10	18	exit	94KL13X
-- 262	2021	7	28	10	18	exit	6P58WS2
-- 263	2021	7	28	10	19	exit	4328GD8
-- 264	2021	7	28	10	20	exit	G412CB7
-- 265	2021	7	28	10	21	exit	L93JTIZ
-- 266	2021	7	28	10	23	exit	322W7JE
-- 267	2021	7	28	10	23	exit	0NTHK55

-- 162	Eugene	2021	7	28	I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money. [Morning 28/7/2021; ATM on Leggett St]

SELECT * FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw';
-- 246	28500762	2021	7	28	Leggett Street	withdraw	48
-- 264	28296815	2021	7	28	Leggett Street	withdraw	20
-- 266	76054385	2021	7	28	Leggett Street	withdraw	60
-- 267	49610011	2021	7	28	Leggett Street	withdraw	50
-- 269	16153065	2021	7	28	Leggett Street	withdraw	80
-- 288	25506511	2021	7	28	Leggett Street	withdraw	20
-- 313	81061156	2021	7	28	Leggett Street	withdraw	30
-- 336	26013199	2021	7	28	Leggett Street	withdraw	35

SELECT * FROM atm_transactions atm
INNER JOIN bank_accounts b ON atm.account_number = b.account_number 
INNER JOIN people p ON p.id = b.person_id
WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw'
AND p.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND p.license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30)
AND p.passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT id FROM flights 
WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour, minute ASC LIMIT 1));

-- 267|49610011|2021|7|28|Leggett Street|withdraw|50|49610011|686048|2010|686048|Bruce|(367) 555-5533|5773159633|94KL13X


-- 163	Raymond	2021	7	28	As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. [28/7/2021; Call; <1 min; flight tomorrow]

SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- 221|(130) 555-0289|(996) 555-8899|2021|7|28|51
-- 224|(499) 555-9472|(892) 555-8872|2021|7|28|36
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45
-- 251|(499) 555-9472|(717) 555-1342|2021|7|28|50
-- 254|(286) 555-6063|(676) 555-6554|2021|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2021|7|28|49
-- 261|(031) 555-6622|(910) 555-3251|2021|7|28|38
-- 279|(826) 555-1652|(066) 555-9701|2021|7|28|55
-- 281|(338) 555-6650|(704) 555-2131|2021|7|28|54

SELECT * FROM phone_calls pc
INNER JOIN people p ON p.phone_number = pc.caller
WHERE pc.year = 2021 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60 AND p.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6);

SELECT id FROM flights 
WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour, minute ASC;

-- 36|8|4|2021|7|29|8|20
-- 43|8|1|2021|7|29|9|30
-- 23|8|11|2021|7|29|12|15
-- 53|8|9|2021|7|29|15|20
-- 18|8|6|2021|7|29|16|0

SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT id FROM flights 
WHERE year = 2021 AND month = 7 AND day = 28 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
ORDER BY hour, minute ASC LIMIT 3);

SELECT * FROM flights f
INNER JOIN passengers p ON p.flight_id = f.id
WHERE p.passport_number = '5773159633';

SELECT * FROM airports WHERE id = 4;
-- 4	LGA	LaGuardia Airport	New York City

SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller = '(367) 555-5533';
-- (375) 555-8161

SELECT name FROM people WHERE phone_number = '(375) 555-8161';
-- Robin