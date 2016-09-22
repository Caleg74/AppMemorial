--
-- PostgreSQL database cluster dump
--

-- Started on 2016-09-22 17:38:37

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE ginnastica_readonly;
ALTER ROLE ginnastica_readonly WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN NOREPLICATION NOBYPASSRLS PASSWORD 'md53879181d4bbaa1afb1206d5e2ccb8f6c' VALID UNTIL '2099-12-31 00:00:00+01';
CREATE ROLE ginnastica_user;
ALTER ROLE ginnastica_user WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN NOREPLICATION NOBYPASSRLS PASSWORD 'md5864b3473fc28425d46bb1db1fcd8201f' VALID UNTIL '2099-12-31 00:00:00+01';
CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION BYPASSRLS PASSWORD 'md5a0ae9d67955152534597252476384f8b';






--
-- Database creation
--

CREATE DATABASE ginnastica WITH TEMPLATE = template0 OWNER = postgres;
REVOKE ALL ON DATABASE ginnastica FROM PUBLIC;
REVOKE ALL ON DATABASE ginnastica FROM postgres;
GRANT ALL ON DATABASE ginnastica TO postgres;
GRANT CONNECT,TEMPORARY ON DATABASE ginnastica TO PUBLIC;
GRANT CONNECT ON DATABASE ginnastica TO ginnastica_readonly;
REVOKE ALL ON DATABASE template1 FROM PUBLIC;
REVOKE ALL ON DATABASE template1 FROM postgres;
GRANT ALL ON DATABASE template1 TO postgres;
GRANT CONNECT ON DATABASE template1 TO PUBLIC;


\connect ginnastica

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.3
-- Dumped by pg_dump version 9.5.3

-- Started on 2016-09-22 17:38:37

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 1 (class 3079 OID 12355)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2205 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- TOC entry 181 (class 1259 OID 16395)
-- Name: apparatus_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE apparatus_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE apparatus_seq OWNER TO ginnastica_user;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 182 (class 1259 OID 16397)
-- Name: apparatus; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE apparatus (
    id integer DEFAULT nextval('apparatus_seq'::regclass) NOT NULL,
    name_it character varying(50) NOT NULL,
    name_en character varying(50) NOT NULL,
    gender character(1) NOT NULL,
    sequence integer NOT NULL
);


ALTER TABLE apparatus OWNER TO ginnastica_user;

--
-- TOC entry 183 (class 1259 OID 16401)
-- Name: athlete_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE athlete_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE athlete_seq OWNER TO ginnastica_user;

--
-- TOC entry 184 (class 1259 OID 16403)
-- Name: athlete; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE athlete (
    id integer DEFAULT nextval('athlete_seq'::regclass) NOT NULL,
    first_name character(50) NOT NULL,
    last_name character(50) NOT NULL,
    gender character(1) NOT NULL,
    nation_id integer NOT NULL
);


ALTER TABLE athlete OWNER TO ginnastica_user;

--
-- TOC entry 185 (class 1259 OID 16407)
-- Name: nations; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE nations (
    id integer NOT NULL,
    name text NOT NULL,
    nicename text NOT NULL,
    iso3 character(3),
    numcode integer,
    phonecode integer NOT NULL,
    iso character(2) NOT NULL,
    ioc character(3) DEFAULT '   '::bpchar NOT NULL
);


ALTER TABLE nations OWNER TO ginnastica_user;

--
-- TOC entry 186 (class 1259 OID 16414)
-- Name: athlete_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW athlete_vw AS
 SELECT athlete.id,
    athlete.first_name,
    athlete.last_name,
    athlete.gender,
    nations.nicename AS nation
   FROM (athlete
     LEFT JOIN nations ON ((athlete.nation_id = nations.id)));


ALTER TABLE athlete_vw OWNER TO ginnastica_user;

--
-- TOC entry 187 (class 1259 OID 16418)
-- Name: city_cup_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE city_cup_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE city_cup_seq OWNER TO ginnastica_user;

--
-- TOC entry 188 (class 1259 OID 16420)
-- Name: city_cup; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE city_cup (
    id integer DEFAULT nextval('city_cup_seq'::regclass) NOT NULL,
    sport_event_id integer NOT NULL,
    apparatus_id integer NOT NULL
);


ALTER TABLE city_cup OWNER TO ginnastica_user;

--
-- TOC entry 189 (class 1259 OID 16424)
-- Name: location_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE location_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE location_seq OWNER TO ginnastica_user;

--
-- TOC entry 190 (class 1259 OID 16426)
-- Name: location; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE location (
    id integer DEFAULT nextval('location_seq'::regclass) NOT NULL,
    name character varying(50) NOT NULL,
    address text,
    city character varying(50),
    zip character varying(10),
    nation_id integer
);


ALTER TABLE location OWNER TO ginnastica_user;

--
-- TOC entry 191 (class 1259 OID 16433)
-- Name: scores_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE scores_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE scores_seq OWNER TO ginnastica_user;

--
-- TOC entry 192 (class 1259 OID 16435)
-- Name: scores; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE scores (
    id integer DEFAULT nextval('scores_seq'::regclass) NOT NULL,
    sport_event_id integer NOT NULL,
    athlete_id integer NOT NULL,
    apparatus_id integer NOT NULL,
    start_score real NOT NULL,
    final_score real NOT NULL,
    force_score integer DEFAULT 0 NOT NULL
);


ALTER TABLE scores OWNER TO ginnastica_user;

--
-- TOC entry 193 (class 1259 OID 16439)
-- Name: sport_event_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE sport_event_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE sport_event_seq OWNER TO ginnastica_user;

--
-- TOC entry 194 (class 1259 OID 16441)
-- Name: sport_event; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE sport_event (
    id integer DEFAULT nextval('sport_event_seq'::regclass) NOT NULL,
    location_id integer NOT NULL,
    year date NOT NULL,
    name character varying(50) NOT NULL
);


ALTER TABLE sport_event OWNER TO ginnastica_user;

--
-- TOC entry 195 (class 1259 OID 16445)
-- Name: scores_male_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW scores_male_vw AS
 SELECT athlete.id,
    athlete.first_name,
    athlete.last_name,
    ( SELECT nations_1.ioc
           FROM nations nations_1
          WHERE (nations_1.id = athlete.nation_id)) AS nation,
    apparatus.name_it AS apparatus,
    scores.start_score,
    scores.final_score,
    sport_event.year
   FROM ((((scores
     LEFT JOIN athlete ON ((scores.athlete_id = athlete.id)))
     LEFT JOIN nations ON ((scores.athlete_id = athlete.nation_id)))
     LEFT JOIN apparatus ON ((scores.apparatus_id = apparatus.id)))
     LEFT JOIN sport_event ON ((scores.sport_event_id = sport_event.id)));


ALTER TABLE scores_male_vw OWNER TO ginnastica_user;

--
-- TOC entry 196 (class 1259 OID 16450)
-- Name: sport_event_subscriptions_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE sport_event_subscriptions_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE sport_event_subscriptions_seq OWNER TO ginnastica_user;

--
-- TOC entry 197 (class 1259 OID 16452)
-- Name: sport_event_subscriptions; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE sport_event_subscriptions (
    id integer DEFAULT nextval('sport_event_subscriptions_seq'::regclass) NOT NULL,
    athlete_id integer NOT NULL,
    sport_event_id integer NOT NULL
);


ALTER TABLE sport_event_subscriptions OWNER TO ginnastica_user;

--
-- TOC entry 2184 (class 0 OID 16397)
-- Dependencies: 182
-- Data for Name: apparatus; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY apparatus (id, name_it, name_en, gender, sequence) FROM stdin;
1	Suolo	Floor	M	1
2	Cavallo a maniglie	Pommel horse	M	2
3	Anelli	Rings	M	3
4	Volteggio	Vault	M	4
5	Parallele	Parallel bars	M	5
6	Sbarra	Horizontal bar	M	6
7	Volteggio	Vault	F	1
8	Parallele asimmetriche	Uneven bars	F	2
9	Trave	Balance beam	F	3
10	Suolo	Floor	F	4
\.


--
-- TOC entry 2223 (class 0 OID 0)
-- Dependencies: 181
-- Name: apparatus_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('apparatus_seq', 10, true);


--
-- TOC entry 2186 (class 0 OID 16403)
-- Dependencies: 184
-- Data for Name: athlete; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY athlete (id, first_name, last_name, gender, nation_id) FROM stdin;
1	Gabriele                                          	Caletti                                           	M	206
4	Silvia                                            	Dos Santos                                        	F	30
8	Giada                                             	Zapatiña                                          	F	16
3	Ciccio                                            	Pasticcio                                         	M	12
9	Grazia                                            	Elegansia                                         	F	33
10	Adriana                                           	Putin                                             	F	177
11	Tiziano                                           	Ferro                                             	M	223
12	Nicolai                                           	Urutcev                                           	M	177
13	Mirka                                             	Caletti                                           	F	13
14	Giona                                             	Rossi                                             	M	206
15	Hans-Rudolf                                       	Zimmermann                                        	M	80
\.


--
-- TOC entry 2224 (class 0 OID 0)
-- Dependencies: 183
-- Name: athlete_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('athlete_seq', 15, true);


--
-- TOC entry 2189 (class 0 OID 16420)
-- Dependencies: 188
-- Data for Name: city_cup; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY city_cup (id, sport_event_id, apparatus_id) FROM stdin;
\.


--
-- TOC entry 2225 (class 0 OID 0)
-- Dependencies: 187
-- Name: city_cup_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('city_cup_seq', 1, false);


--
-- TOC entry 2191 (class 0 OID 16426)
-- Dependencies: 190
-- Data for Name: location; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY location (id, name, address, city, zip, nation_id) FROM stdin;
1	Chiasso		Chiasso	6830	206
\.


--
-- TOC entry 2226 (class 0 OID 0)
-- Dependencies: 189
-- Name: location_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('location_seq', 1, true);


--
-- TOC entry 2187 (class 0 OID 16407)
-- Dependencies: 185
-- Data for Name: nations; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY nations (id, name, nicename, iso3, numcode, phonecode, iso, ioc) FROM stdin;
1	AFGHANISTAN	Afghanistan	AFG	4	93	AF	   
2	ALBANIA	Albania	ALB	8	355	AL	   
3	ALGERIA	Algeria	DZA	12	213	DZ	   
4	AMERICAN SAMOA	American Samoa	ASM	16	1684	AS	   
5	ANDORRA	Andorra	AND	20	376	AD	   
6	ANGOLA	Angola	AGO	24	244	AO	   
7	ANGUILLA	Anguilla	AIA	660	1264	AI	   
8	ANTARCTICA	Antarctica	\N	\N	0	AQ	   
9	ANTIGUA AND BARBUDA	Antigua and Barbuda	ATG	28	1268	AG	   
10	ARGENTINA	Argentina	ARG	32	54	AR	   
11	ARMENIA	Armenia	ARM	51	374	AM	   
12	ARUBA	Aruba	ABW	533	297	AW	   
13	AUSTRALIA	Australia	AUS	36	61	AU	   
14	AUSTRIA	Austria	AUT	40	43	AT	   
15	AZERBAIJAN	Azerbaijan	AZE	31	994	AZ	   
16	BAHAMAS	Bahamas	BHS	44	1242	BS	   
17	BAHRAIN	Bahrain	BHR	48	973	BH	   
18	BANGLADESH	Bangladesh	BGD	50	880	BD	   
19	BARBADOS	Barbados	BRB	52	1246	BB	   
20	BELARUS	Belarus	BLR	112	375	BY	   
21	BELGIUM	Belgium	BEL	56	32	BE	   
22	BELIZE	Belize	BLZ	84	501	BZ	   
23	BENIN	Benin	BEN	204	229	BJ	   
24	BERMUDA	Bermuda	BMU	60	1441	BM	   
25	BHUTAN	Bhutan	BTN	64	975	BT	   
26	BOLIVIA	Bolivia	BOL	68	591	BO	   
27	BOSNIA AND HERZEGOVINA	Bosnia and Herzegovina	BIH	70	387	BA	   
28	BOTSWANA	Botswana	BWA	72	267	BW	   
29	BOUVET ISLAND	Bouvet Island	\N	\N	0	BV	   
30	BRAZIL	Brazil	BRA	76	55	BR	   
31	BRITISH INDIAN OCEAN TERRITORY	British Indian Ocean Territory	\N	\N	246	IO	   
32	BRUNEI DARUSSALAM	Brunei Darussalam	BRN	96	673	BN	   
33	BULGARIA	Bulgaria	BGR	100	359	BG	   
34	BURKINA FASO	Burkina Faso	BFA	854	226	BF	   
35	BURUNDI	Burundi	BDI	108	257	BI	   
36	CAMBODIA	Cambodia	KHM	116	855	KH	   
37	CAMEROON	Cameroon	CMR	120	237	CM	   
38	CANADA	Canada	CAN	124	1	CA	   
39	CAPE VERDE	Cape Verde	CPV	132	238	CV	   
40	CAYMAN ISLANDS	Cayman Islands	CYM	136	1345	KY	   
41	CENTRAL AFRICAN REPUBLIC	Central African Republic	CAF	140	236	CF	   
42	CHAD	Chad	TCD	148	235	TD	   
43	CHILE	Chile	CHL	152	56	CL	   
44	CHINA	China	CHN	156	86	CN	   
45	CHRISTMAS ISLAND	Christmas Island	\N	\N	61	CX	   
46	COCOS (KEELING) ISLANDS	Cocos (Keeling) Islands	\N	\N	672	CC	   
47	COLOMBIA	Colombia	COL	170	57	CO	   
48	COMOROS	Comoros	COM	174	269	KM	   
49	CONGO	Congo	COG	178	242	CG	   
50	CONGO, THE DEMOCRATIC REPUBLIC OF THE	Congo, the Democratic Republic of the	COD	180	242	CD	   
51	COOK ISLANDS	Cook Islands	COK	184	682	CK	   
52	COSTA RICA	Costa Rica	CRI	188	506	CR	   
53	COTE D'IVOIRE	Cote D'Ivoire	CIV	384	225	CI	   
54	CROATIA	Croatia	HRV	191	385	HR	   
55	CUBA	Cuba	CUB	192	53	CU	   
56	CYPRUS	Cyprus	CYP	196	357	CY	   
57	CZECH REPUBLIC	Czech Republic	CZE	203	420	CZ	   
58	DENMARK	Denmark	DNK	208	45	DK	   
59	DJIBOUTI	Djibouti	DJI	262	253	DJ	   
60	DOMINICA	Dominica	DMA	212	1767	DM	   
61	DOMINICAN REPUBLIC	Dominican Republic	DOM	214	1809	DO	   
62	ECUADOR	Ecuador	ECU	218	593	EC	   
63	EGYPT	Egypt	EGY	818	20	EG	   
64	EL SALVADOR	El Salvador	SLV	222	503	SV	   
65	EQUATORIAL GUINEA	Equatorial Guinea	GNQ	226	240	GQ	   
66	ERITREA	Eritrea	ERI	232	291	ER	   
67	ESTONIA	Estonia	EST	233	372	EE	   
68	ETHIOPIA	Ethiopia	ETH	231	251	ET	   
69	FALKLAND ISLANDS (MALVINAS)	Falkland Islands (Malvinas)	FLK	238	500	FK	   
70	FAROE ISLANDS	Faroe Islands	FRO	234	298	FO	   
71	FIJI	Fiji	FJI	242	679	FJ	   
72	FINLAND	Finland	FIN	246	358	FI	   
73	FRANCE	France	FRA	250	33	FR	   
74	FRENCH GUIANA	French Guiana	GUF	254	594	GF	   
75	FRENCH POLYNESIA	French Polynesia	PYF	258	689	PF	   
76	FRENCH SOUTHERN TERRITORIES	French Southern Territories	\N	\N	0	TF	   
77	GABON	Gabon	GAB	266	241	GA	   
78	GAMBIA	Gambia	GMB	270	220	GM	   
79	GEORGIA	Georgia	GEO	268	995	GE	   
80	GERMANY	Germany	DEU	276	49	DE	   
81	GHANA	Ghana	GHA	288	233	GH	   
82	GIBRALTAR	Gibraltar	GIB	292	350	GI	   
83	GREECE	Greece	GRC	300	30	GR	   
84	GREENLAND	Greenland	GRL	304	299	GL	   
85	GRENADA	Grenada	GRD	308	1473	GD	   
86	GUADELOUPE	Guadeloupe	GLP	312	590	GP	   
87	GUAM	Guam	GUM	316	1671	GU	   
88	GUATEMALA	Guatemala	GTM	320	502	GT	   
89	GUINEA	Guinea	GIN	324	224	GN	   
90	GUINEA-BISSAU	Guinea-Bissau	GNB	624	245	GW	   
91	GUYANA	Guyana	GUY	328	592	GY	   
92	HAITI	Haiti	HTI	332	509	HT	   
93	HEARD ISLAND AND MCDONALD ISLANDS	Heard Island and Mcdonald Islands	\N	\N	0	HM	   
94	HOLY SEE (VATICAN CITY STATE)	Holy See (Vatican City State)	VAT	336	39	VA	   
95	HONDURAS	Honduras	HND	340	504	HN	   
96	HONG KONG	Hong Kong	HKG	344	852	HK	   
97	HUNGARY	Hungary	HUN	348	36	HU	   
98	ICELAND	Iceland	ISL	352	354	IS	   
99	INDIA	India	IND	356	91	IN	   
100	INDONESIA	Indonesia	IDN	360	62	ID	   
101	IRAN, ISLAMIC REPUBLIC OF	Iran, Islamic Republic of	IRN	364	98	IR	   
102	IRAQ	Iraq	IRQ	368	964	IQ	   
103	IRELAND	Ireland	IRL	372	353	IE	   
104	ISRAEL	Israel	ISR	376	972	IL	   
105	ITALY	Italy	ITA	380	39	IT	   
106	JAMAICA	Jamaica	JAM	388	1876	JM	   
107	JAPAN	Japan	JPN	392	81	JP	   
108	JORDAN	Jordan	JOR	400	962	JO	   
109	KAZAKHSTAN	Kazakhstan	KAZ	398	7	KZ	   
110	KENYA	Kenya	KEN	404	254	KE	   
111	KIRIBATI	Kiribati	KIR	296	686	KI	   
112	KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF	Korea, Democratic People's Republic of	PRK	408	850	KP	   
113	KOREA, REPUBLIC OF	Korea, Republic of	KOR	410	82	KR	   
114	KUWAIT	Kuwait	KWT	414	965	KW	   
115	KYRGYZSTAN	Kyrgyzstan	KGZ	417	996	KG	   
116	LAO PEOPLE'S DEMOCRATIC REPUBLIC	Lao People's Democratic Republic	LAO	418	856	LA	   
117	LATVIA	Latvia	LVA	428	371	LV	   
118	LEBANON	Lebanon	LBN	422	961	LB	   
119	LESOTHO	Lesotho	LSO	426	266	LS	   
120	LIBERIA	Liberia	LBR	430	231	LR	   
121	LIBYAN ARAB JAMAHIRIYA	Libyan Arab Jamahiriya	LBY	434	218	LY	   
122	LIECHTENSTEIN	Liechtenstein	LIE	438	423	LI	   
123	LITHUANIA	Lithuania	LTU	440	370	LT	   
124	LUXEMBOURG	Luxembourg	LUX	442	352	LU	   
125	MACAO	Macao	MAC	446	853	MO	   
126	MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF	Macedonia, the Former Yugoslav Republic of	MKD	807	389	MK	   
127	MADAGASCAR	Madagascar	MDG	450	261	MG	   
128	MALAWI	Malawi	MWI	454	265	MW	   
129	MALAYSIA	Malaysia	MYS	458	60	MY	   
130	MALDIVES	Maldives	MDV	462	960	MV	   
131	MALI	Mali	MLI	466	223	ML	   
132	MALTA	Malta	MLT	470	356	MT	   
133	MARSHALL ISLANDS	Marshall Islands	MHL	584	692	MH	   
134	MARTINIQUE	Martinique	MTQ	474	596	MQ	   
135	MAURITANIA	Mauritania	MRT	478	222	MR	   
136	MAURITIUS	Mauritius	MUS	480	230	MU	   
137	MAYOTTE	Mayotte	\N	\N	269	YT	   
138	MEXICO	Mexico	MEX	484	52	MX	   
139	MICRONESIA, FEDERATED STATES OF	Micronesia, Federated States of	FSM	583	691	FM	   
140	MOLDOVA, REPUBLIC OF	Moldova, Republic of	MDA	498	373	MD	   
141	MONACO	Monaco	MCO	492	377	MC	   
142	MONGOLIA	Mongolia	MNG	496	976	MN	   
143	MONTSERRAT	Montserrat	MSR	500	1664	MS	   
144	MOROCCO	Morocco	MAR	504	212	MA	   
145	MOZAMBIQUE	Mozambique	MOZ	508	258	MZ	   
146	MYANMAR	Myanmar	MMR	104	95	MM	   
147	NAMIBIA	Namibia	NAM	516	264	NA	   
148	NAURU	Nauru	NRU	520	674	NR	   
149	NEPAL	Nepal	NPL	524	977	NP	   
150	NETHERLANDS	Netherlands	NLD	528	31	NL	   
151	NETHERLANDS ANTILLES	Netherlands Antilles	ANT	530	599	AN	   
152	NEW CALEDONIA	New Caledonia	NCL	540	687	NC	   
153	NEW ZEALAND	New Zealand	NZL	554	64	NZ	   
154	NICARAGUA	Nicaragua	NIC	558	505	NI	   
155	NIGER	Niger	NER	562	227	NE	   
156	NIGERIA	Nigeria	NGA	566	234	NG	   
157	NIUE	Niue	NIU	570	683	NU	   
158	NORFOLK ISLAND	Norfolk Island	NFK	574	672	NF	   
159	NORTHERN MARIANA ISLANDS	Northern Mariana Islands	MNP	580	1670	MP	   
160	NORWAY	Norway	NOR	578	47	NO	   
161	OMAN	Oman	OMN	512	968	OM	   
162	PAKISTAN	Pakistan	PAK	586	92	PK	   
163	PALAU	Palau	PLW	585	680	PW	   
164	PALESTINIAN TERRITORY, OCCUPIED	Palestinian Territory, Occupied	\N	\N	970	PS	   
165	PANAMA	Panama	PAN	591	507	PA	   
166	PAPUA NEW GUINEA	Papua New Guinea	PNG	598	675	PG	   
167	PARAGUAY	Paraguay	PRY	600	595	PY	   
168	PERU	Peru	PER	604	51	PE	   
169	PHILIPPINES	Philippines	PHL	608	63	PH	   
170	PITCAIRN	Pitcairn	PCN	612	0	PN	   
171	POLAND	Poland	POL	616	48	PL	   
172	PORTUGAL	Portugal	PRT	620	351	PT	   
173	PUERTO RICO	Puerto Rico	PRI	630	1787	PR	   
174	QATAR	Qatar	QAT	634	974	QA	   
175	REUNION	Reunion	REU	638	262	RE	   
176	ROMANIA	Romania	ROM	642	40	RO	   
177	RUSSIAN FEDERATION	Russian Federation	RUS	643	70	RU	   
178	RWANDA	Rwanda	RWA	646	250	RW	   
179	SAINT HELENA	Saint Helena	SHN	654	290	SH	   
180	SAINT KITTS AND NEVIS	Saint Kitts and Nevis	KNA	659	1869	KN	   
181	SAINT LUCIA	Saint Lucia	LCA	662	1758	LC	   
182	SAINT PIERRE AND MIQUELON	Saint Pierre and Miquelon	SPM	666	508	PM	   
183	SAINT VINCENT AND THE GRENADINES	Saint Vincent and the Grenadines	VCT	670	1784	VC	   
184	SAMOA	Samoa	WSM	882	684	WS	   
185	SAN MARINO	San Marino	SMR	674	378	SM	   
186	SAO TOME AND PRINCIPE	Sao Tome and Principe	STP	678	239	ST	   
187	SAUDI ARABIA	Saudi Arabia	SAU	682	966	SA	   
188	SENEGAL	Senegal	SEN	686	221	SN	   
189	SERBIA AND MONTENEGRO	Serbia and Montenegro	\N	\N	381	CS	   
190	SEYCHELLES	Seychelles	SYC	690	248	SC	   
191	SIERRA LEONE	Sierra Leone	SLE	694	232	SL	   
192	SINGAPORE	Singapore	SGP	702	65	SG	   
193	SLOVAKIA	Slovakia	SVK	703	421	SK	   
194	SLOVENIA	Slovenia	SVN	705	386	SI	   
195	SOLOMON ISLANDS	Solomon Islands	SLB	90	677	SB	   
196	SOMALIA	Somalia	SOM	706	252	SO	   
197	SOUTH AFRICA	South Africa	ZAF	710	27	ZA	   
198	SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS	South Georgia and the South Sandwich Islands	\N	\N	0	GS	   
199	SPAIN	Spain	ESP	724	34	ES	   
200	SRI LANKA	Sri Lanka	LKA	144	94	LK	   
201	SUDAN	Sudan	SDN	736	249	SD	   
202	SURINAME	Suriname	SUR	740	597	SR	   
203	SVALBARD AND JAN MAYEN	Svalbard and Jan Mayen	SJM	744	47	SJ	   
204	SWAZILAND	Swaziland	SWZ	748	268	SZ	   
205	SWEDEN	Sweden	SWE	752	46	SE	   
207	SYRIAN ARAB REPUBLIC	Syrian Arab Republic	SYR	760	963	SY	   
208	TAIWAN, PROVINCE OF CHINA	Taiwan, Province of China	TWN	158	886	TW	   
209	TAJIKISTAN	Tajikistan	TJK	762	992	TJ	   
210	TANZANIA, UNITED REPUBLIC OF	Tanzania, United Republic of	TZA	834	255	TZ	   
211	THAILAND	Thailand	THA	764	66	TH	   
212	TIMOR-LESTE	Timor-Leste	\N	\N	670	TL	   
213	TOGO	Togo	TGO	768	228	TG	   
214	TOKELAU	Tokelau	TKL	772	690	TK	   
215	TONGA	Tonga	TON	776	676	TO	   
216	TRINIDAD AND TOBAGO	Trinidad and Tobago	TTO	780	1868	TT	   
217	TUNISIA	Tunisia	TUN	788	216	TN	   
218	TURKEY	Turkey	TUR	792	90	TR	   
219	TURKMENISTAN	Turkmenistan	TKM	795	7370	TM	   
220	TURKS AND CAICOS ISLANDS	Turks and Caicos Islands	TCA	796	1649	TC	   
221	TUVALU	Tuvalu	TUV	798	688	TV	   
222	UGANDA	Uganda	UGA	800	256	UG	   
223	UKRAINE	Ukraine	UKR	804	380	UA	   
224	UNITED ARAB EMIRATES	United Arab Emirates	ARE	784	971	AE	   
225	UNITED KINGDOM	United Kingdom	GBR	826	44	GB	   
226	UNITED STATES	United States	USA	840	1	US	   
227	UNITED STATES MINOR OUTLYING ISLANDS	United States Minor Outlying Islands	\N	\N	1	UM	   
228	URUGUAY	Uruguay	URY	858	598	UY	   
229	UZBEKISTAN	Uzbekistan	UZB	860	998	UZ	   
230	VANUATU	Vanuatu	VUT	548	678	VU	   
231	VENEZUELA	Venezuela	VEN	862	58	VE	   
232	VIET NAM	Viet Nam	VNM	704	84	VN	   
233	VIRGIN ISLANDS, BRITISH	Virgin Islands, British	VGB	92	1284	VG	   
234	VIRGIN ISLANDS, U.S.	Virgin Islands, U.s.	VIR	850	1340	VI	   
235	WALLIS AND FUTUNA	Wallis and Futuna	WLF	876	681	WF	   
236	WESTERN SAHARA	Western Sahara	ESH	732	212	EH	   
237	YEMEN	Yemen	YEM	887	967	YE	   
238	ZAMBIA	Zambia	ZMB	894	260	ZM	   
239	ZIMBABWE	Zimbabwe	ZWE	716	263	ZW	   
206	SWITZERLAND	Switzerland	CHE	756	41	CH	SUI
\.


--
-- TOC entry 2193 (class 0 OID 16435)
-- Dependencies: 192
-- Data for Name: scores; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY scores (id, sport_event_id, athlete_id, apparatus_id, start_score, final_score, force_score) FROM stdin;
27	1	3	2	3.23300004	12.5410004	0
34	1	10	7	5.67799997	14.7290001	0
17	1	1	1	2.31999993	12.3199997	0
23	1	1	4	5.55000019	15.5500002	0
25	1	1	6	7.76999998	17.7700005	0
35	1	15	3	6.23400021	15.309	0
19	1	3	1	2.35599995	11.9989996	0
30	1	3	6	7.76999998	17.7700005	1
14	1	1	3	1.11000001	11.1099997	0
15	1	3	10	2	12	0
16	1	8	10	5.34000015	14.5600004	0
22	1	1	2	3.32999992	13.3299999	0
21	1	10	9	2.1099999	11.1099997	0
24	1	1	5	6.65999985	16.6599998	0
26	1	3	5	6.65999985	16.6599998	0
28	1	3	3	6.65999985	16.6599998	0
29	1	3	4	6.65999985	16.6599998	0
31	1	13	8	3.25	14.5869999	0
32	1	10	8	2.45000005	11.5670004	0
33	1	14	3	3.22000003	12.5699997	0
\.


--
-- TOC entry 2227 (class 0 OID 0)
-- Dependencies: 191
-- Name: scores_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('scores_seq', 35, true);


--
-- TOC entry 2195 (class 0 OID 16441)
-- Dependencies: 194
-- Data for Name: sport_event; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY sport_event (id, location_id, year, name) FROM stdin;
1	1	2016-11-02	Memorial Arturo Gander
\.


--
-- TOC entry 2228 (class 0 OID 0)
-- Dependencies: 193
-- Name: sport_event_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('sport_event_seq', 1, true);


--
-- TOC entry 2197 (class 0 OID 16452)
-- Dependencies: 197
-- Data for Name: sport_event_subscriptions; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY sport_event_subscriptions (id, athlete_id, sport_event_id) FROM stdin;
34	10	1
35	3	1
38	1	1
41	9	1
42	4	1
43	12	1
44	11	1
45	13	1
46	14	1
47	15	1
\.


--
-- TOC entry 2229 (class 0 OID 0)
-- Dependencies: 196
-- Name: sport_event_subscriptions_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('sport_event_subscriptions_seq', 47, true);


--
-- TOC entry 2042 (class 2606 OID 16457)
-- Name: apparatus_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY apparatus
    ADD CONSTRAINT apparatus_id_pk PRIMARY KEY (id);


--
-- TOC entry 2044 (class 2606 OID 16459)
-- Name: athlete_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY athlete
    ADD CONSTRAINT athlete_id_pk PRIMARY KEY (id);


--
-- TOC entry 2048 (class 2606 OID 16461)
-- Name: city_cup_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY city_cup
    ADD CONSTRAINT city_cup_id_pk PRIMARY KEY (id);


--
-- TOC entry 2050 (class 2606 OID 16463)
-- Name: location_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY location
    ADD CONSTRAINT location_id_pk PRIMARY KEY (id);


--
-- TOC entry 2046 (class 2606 OID 16465)
-- Name: nation_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY nations
    ADD CONSTRAINT nation_pk PRIMARY KEY (id);


--
-- TOC entry 2052 (class 2606 OID 16467)
-- Name: scores_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY scores
    ADD CONSTRAINT scores_id_pk PRIMARY KEY (id);


--
-- TOC entry 2054 (class 2606 OID 16469)
-- Name: sport_event_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY sport_event
    ADD CONSTRAINT sport_event_id_pk PRIMARY KEY (id);


--
-- TOC entry 2056 (class 2606 OID 16471)
-- Name: sport_event_subscriptions_pkey; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY sport_event_subscriptions
    ADD CONSTRAINT sport_event_subscriptions_pkey PRIMARY KEY (id);


--
-- TOC entry 2058 (class 2606 OID 16472)
-- Name: apparatus_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY city_cup
    ADD CONSTRAINT apparatus_id_fk FOREIGN KEY (apparatus_id) REFERENCES apparatus(id);


--
-- TOC entry 2061 (class 2606 OID 16477)
-- Name: apparatus_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY scores
    ADD CONSTRAINT apparatus_id_fk FOREIGN KEY (apparatus_id) REFERENCES apparatus(id);


--
-- TOC entry 2062 (class 2606 OID 16482)
-- Name: athlete_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY scores
    ADD CONSTRAINT athlete_id_fk FOREIGN KEY (athlete_id) REFERENCES athlete(id);


--
-- TOC entry 2064 (class 2606 OID 16487)
-- Name: location_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY sport_event
    ADD CONSTRAINT location_id_fk FOREIGN KEY (location_id) REFERENCES location(id);


--
-- TOC entry 2057 (class 2606 OID 16492)
-- Name: nation_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY athlete
    ADD CONSTRAINT nation_id_fk FOREIGN KEY (nation_id) REFERENCES nations(id) ON UPDATE CASCADE;


--
-- TOC entry 2060 (class 2606 OID 16497)
-- Name: nation_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY location
    ADD CONSTRAINT nation_id_fk FOREIGN KEY (nation_id) REFERENCES nations(id);


--
-- TOC entry 2059 (class 2606 OID 16502)
-- Name: sport_event_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY city_cup
    ADD CONSTRAINT sport_event_id_fk FOREIGN KEY (sport_event_id) REFERENCES sport_event(id);


--
-- TOC entry 2063 (class 2606 OID 16507)
-- Name: sport_event_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY scores
    ADD CONSTRAINT sport_event_id_fk FOREIGN KEY (sport_event_id) REFERENCES sport_event(id);


--
-- TOC entry 2065 (class 2606 OID 16512)
-- Name: sport_event_subscriptions_athlete_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY sport_event_subscriptions
    ADD CONSTRAINT sport_event_subscriptions_athlete_id_fkey FOREIGN KEY (athlete_id) REFERENCES athlete(id);


--
-- TOC entry 2066 (class 2606 OID 16517)
-- Name: sport_event_subscriptions_sport_event_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY sport_event_subscriptions
    ADD CONSTRAINT sport_event_subscriptions_sport_event_id_fkey FOREIGN KEY (sport_event_id) REFERENCES sport_event(id);


--
-- TOC entry 2204 (class 0 OID 0)
-- Dependencies: 7
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;
GRANT USAGE ON SCHEMA public TO ginnastica_readonly;


--
-- TOC entry 2206 (class 0 OID 0)
-- Dependencies: 181
-- Name: apparatus_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON SEQUENCE apparatus_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE apparatus_seq FROM ginnastica_user;
GRANT ALL ON SEQUENCE apparatus_seq TO ginnastica_user;
GRANT SELECT ON SEQUENCE apparatus_seq TO ginnastica_readonly;


--
-- TOC entry 2207 (class 0 OID 0)
-- Dependencies: 182
-- Name: apparatus; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE apparatus FROM PUBLIC;
REVOKE ALL ON TABLE apparatus FROM ginnastica_user;
GRANT ALL ON TABLE apparatus TO ginnastica_user;
GRANT SELECT ON TABLE apparatus TO ginnastica_readonly;


--
-- TOC entry 2208 (class 0 OID 0)
-- Dependencies: 183
-- Name: athlete_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON SEQUENCE athlete_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE athlete_seq FROM ginnastica_user;
GRANT ALL ON SEQUENCE athlete_seq TO ginnastica_user;
GRANT SELECT ON SEQUENCE athlete_seq TO ginnastica_readonly;


--
-- TOC entry 2209 (class 0 OID 0)
-- Dependencies: 184
-- Name: athlete; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE athlete FROM PUBLIC;
REVOKE ALL ON TABLE athlete FROM ginnastica_user;
GRANT ALL ON TABLE athlete TO ginnastica_user;
GRANT SELECT ON TABLE athlete TO ginnastica_readonly;


--
-- TOC entry 2210 (class 0 OID 0)
-- Dependencies: 185
-- Name: nations; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE nations FROM PUBLIC;
REVOKE ALL ON TABLE nations FROM ginnastica_user;
GRANT ALL ON TABLE nations TO ginnastica_user;
GRANT SELECT ON TABLE nations TO ginnastica_readonly;


--
-- TOC entry 2211 (class 0 OID 0)
-- Dependencies: 186
-- Name: athlete_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE athlete_vw FROM PUBLIC;
REVOKE ALL ON TABLE athlete_vw FROM ginnastica_user;
GRANT ALL ON TABLE athlete_vw TO ginnastica_user;
GRANT SELECT ON TABLE athlete_vw TO ginnastica_readonly;


--
-- TOC entry 2212 (class 0 OID 0)
-- Dependencies: 187
-- Name: city_cup_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON SEQUENCE city_cup_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE city_cup_seq FROM ginnastica_user;
GRANT ALL ON SEQUENCE city_cup_seq TO ginnastica_user;
GRANT SELECT ON SEQUENCE city_cup_seq TO ginnastica_readonly;


--
-- TOC entry 2213 (class 0 OID 0)
-- Dependencies: 188
-- Name: city_cup; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE city_cup FROM PUBLIC;
REVOKE ALL ON TABLE city_cup FROM ginnastica_user;
GRANT ALL ON TABLE city_cup TO ginnastica_user;
GRANT SELECT ON TABLE city_cup TO ginnastica_readonly;


--
-- TOC entry 2214 (class 0 OID 0)
-- Dependencies: 189
-- Name: location_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON SEQUENCE location_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE location_seq FROM ginnastica_user;
GRANT ALL ON SEQUENCE location_seq TO ginnastica_user;
GRANT SELECT ON SEQUENCE location_seq TO ginnastica_readonly;


--
-- TOC entry 2215 (class 0 OID 0)
-- Dependencies: 190
-- Name: location; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE location FROM PUBLIC;
REVOKE ALL ON TABLE location FROM ginnastica_user;
GRANT ALL ON TABLE location TO ginnastica_user;
GRANT SELECT ON TABLE location TO ginnastica_readonly;


--
-- TOC entry 2216 (class 0 OID 0)
-- Dependencies: 191
-- Name: scores_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON SEQUENCE scores_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE scores_seq FROM ginnastica_user;
GRANT ALL ON SEQUENCE scores_seq TO ginnastica_user;
GRANT SELECT ON SEQUENCE scores_seq TO ginnastica_readonly;


--
-- TOC entry 2217 (class 0 OID 0)
-- Dependencies: 192
-- Name: scores; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE scores FROM PUBLIC;
REVOKE ALL ON TABLE scores FROM ginnastica_user;
GRANT ALL ON TABLE scores TO ginnastica_user;
GRANT SELECT ON TABLE scores TO ginnastica_readonly;


--
-- TOC entry 2218 (class 0 OID 0)
-- Dependencies: 193
-- Name: sport_event_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON SEQUENCE sport_event_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE sport_event_seq FROM ginnastica_user;
GRANT ALL ON SEQUENCE sport_event_seq TO ginnastica_user;
GRANT SELECT ON SEQUENCE sport_event_seq TO ginnastica_readonly;


--
-- TOC entry 2219 (class 0 OID 0)
-- Dependencies: 194
-- Name: sport_event; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE sport_event FROM PUBLIC;
REVOKE ALL ON TABLE sport_event FROM ginnastica_user;
GRANT ALL ON TABLE sport_event TO ginnastica_user;
GRANT SELECT ON TABLE sport_event TO ginnastica_readonly;


--
-- TOC entry 2220 (class 0 OID 0)
-- Dependencies: 195
-- Name: scores_male_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE scores_male_vw FROM PUBLIC;
REVOKE ALL ON TABLE scores_male_vw FROM ginnastica_user;
GRANT ALL ON TABLE scores_male_vw TO ginnastica_user;
GRANT SELECT ON TABLE scores_male_vw TO ginnastica_readonly;


--
-- TOC entry 2221 (class 0 OID 0)
-- Dependencies: 196
-- Name: sport_event_subscriptions_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON SEQUENCE sport_event_subscriptions_seq FROM PUBLIC;
REVOKE ALL ON SEQUENCE sport_event_subscriptions_seq FROM ginnastica_user;
GRANT ALL ON SEQUENCE sport_event_subscriptions_seq TO ginnastica_user;
GRANT SELECT ON SEQUENCE sport_event_subscriptions_seq TO ginnastica_readonly;


--
-- TOC entry 2222 (class 0 OID 0)
-- Dependencies: 197
-- Name: sport_event_subscriptions; Type: ACL; Schema: public; Owner: ginnastica_user
--

REVOKE ALL ON TABLE sport_event_subscriptions FROM PUBLIC;
REVOKE ALL ON TABLE sport_event_subscriptions FROM ginnastica_user;
GRANT ALL ON TABLE sport_event_subscriptions TO ginnastica_user;
GRANT SELECT ON TABLE sport_event_subscriptions TO ginnastica_readonly;


--
-- TOC entry 1683 (class 826 OID 24578)
-- Name: DEFAULT PRIVILEGES FOR TABLES; Type: DEFAULT ACL; Schema: public; Owner: postgres
--

ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public REVOKE ALL ON TABLES  FROM PUBLIC;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public REVOKE ALL ON TABLES  FROM postgres;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public GRANT SELECT ON TABLES  TO ginnastica_readonly;


-- Completed on 2016-09-22 17:38:37

--
-- PostgreSQL database dump complete
--

\connect postgres

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.3
-- Dumped by pg_dump version 9.5.3

-- Started on 2016-09-22 17:38:37

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 2095 (class 1262 OID 12373)
-- Dependencies: 2094
-- Name: postgres; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE postgres IS 'default administrative connection database';


--
-- TOC entry 2 (class 3079 OID 12355)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2098 (class 0 OID 0)
-- Dependencies: 2
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- TOC entry 1 (class 3079 OID 16384)
-- Name: adminpack; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;


--
-- TOC entry 2099 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION adminpack; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';


--
-- TOC entry 2097 (class 0 OID 0)
-- Dependencies: 7
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2016-09-22 17:38:37

--
-- PostgreSQL database dump complete
--

\connect template1

SET default_transaction_read_only = off;

--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.3
-- Dumped by pg_dump version 9.5.3

-- Started on 2016-09-22 17:38:37

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 2094 (class 1262 OID 1)
-- Dependencies: 2093
-- Name: template1; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON DATABASE template1 IS 'default template for new databases';


--
-- TOC entry 1 (class 3079 OID 12355)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2097 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- TOC entry 2096 (class 0 OID 0)
-- Dependencies: 6
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2016-09-22 17:38:37

--
-- PostgreSQL database dump complete
--

-- Completed on 2016-09-22 17:38:37

--
-- PostgreSQL database cluster dump complete
--

