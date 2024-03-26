-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Firstly .schema to know how the database is formed

-- getting the crime information

SELECT id, description
  FROM crime_scene_reports
 WHERE year = 2023
   AND month = 7
   AND day = 28
   AND street = 'Humphrey Street';

-- crime.id = 295, Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time each of their
-- interview transcripts mentions the bakery.

SELECT id, transcript
  FROM interviews
 WHERE year = 2023
   AND month = 7
   AND day = 28;

/* interview.id = 161 : Sometime <within ten minutes of the theft>, I saw the thief <get into a
car in the bakery parking lot and drive away>. If you have security footage from the bakery
parking lot, you might want to look for cars that left the parking lot in that time frame.

   interview.id = 162 :  I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at Emma's bakery, I was walking by the <ATM on
Leggett Street> and saw the thief there <withdrawing some money>.

   interview.id = 163 :  As the thief was leaving the bakery, they <called someone> who
talked to them for <less than a minute>. In the call, I heard the thief say that they were
planning to <take the earliest flight out of Fiftyville tomorrow>. The thief then asked the
person on the other end of the phone to purchase the flight ticket. */

-- using this data to get the name of the thief

SELECT name
FROM people
WHERE license_plate IN ( -- working with lead from interview 161
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25
    AND activity = 'exit'
)
AND phone_number IN ( -- working with lead from interview 163
    SELECT caller
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND passport_number IN ( -- working with lead from interview 163
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE year = 2023
        AND month = 7
        AND day = 29
        AND origin_airport_id = (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        ORDER BY hour, minute
        LIMIT 1
    )
)
AND id IN ( -- working with lead from interview 162
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);

-- The thief is Bruce
-- getting the city the thief escaped to

SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2023
        AND month = 7
        AND day = 29
        AND origin_airport_id = (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        ORDER BY hour, minute
        LIMIT 1
);

-- The city is New York City
-- getting the accomplice

SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
);

-- The accomplice is Robin
