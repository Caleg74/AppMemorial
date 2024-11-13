--
-- PostgreSQL database cluster dump
--

-- Started on 2024-11-13 08:25:50

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE ginnastica_readonly;
ALTER ROLE ginnastica_readonly WITH NOSUPERUSER INHERIT NOCREATEROLE NOCREATEDB LOGIN NOREPLICATION NOBYPASSRLS PASSWORD 'md53879181d4bbaa1afb1206d5e2ccb8f6c';
CREATE ROLE ginnastica_user;
ALTER ROLE ginnastica_user WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION NOBYPASSRLS PASSWORD 'md5864b3473fc28425d46bb1db1fcd8201f';
CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION BYPASSRLS PASSWORD 'md5a0ae9d67955152534597252476384f8b';


--
-- Role memberships
--

GRANT ginnastica_user TO postgres GRANTED BY postgres;




--
-- Databases
--

--
-- Database "template1" dump
--

\connect template1

--
-- PostgreSQL database dump
--

-- Dumped from database version 12.1
-- Dumped by pg_dump version 12.1

-- Started on 2024-11-13 08:25:50

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

-- Completed on 2024-11-13 08:25:51

--
-- PostgreSQL database dump complete
--

--
-- Database "ginnastica" dump
--

--
-- PostgreSQL database dump
--

-- Dumped from database version 12.1
-- Dumped by pg_dump version 12.1

-- Started on 2024-11-13 08:25:51

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 2937 (class 1262 OID 24588)
-- Name: ginnastica; Type: DATABASE; Schema: -; Owner: ginnastica_user
--

CREATE DATABASE ginnastica WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'English_Switzerland.1252' LC_CTYPE = 'English_Switzerland.1252';


ALTER DATABASE ginnastica OWNER TO ginnastica_user;

\connect ginnastica

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 1 (class 3079 OID 24743)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2939 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- TOC entry 222 (class 1255 OID 24748)
-- Name: sync_modification_date_fn(); Type: FUNCTION; Schema: public; Owner: ginnastica_user
--

CREATE FUNCTION public.sync_modification_date_fn() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
IF TG_OP = 'INSERT' THEN
    IF NEW.created IS NULL THEN
        NEW.created = NOW();
    END IF;

    IF NEW.last_modified IS NULL THEN
        NEW.last_modified = NOW();
    END IF;

ELSIF TG_OP = 'UPDATE' THEN

    NEW.last_modified = NOW();

END IF;

RETURN NEW;
END;
$$;


ALTER FUNCTION public.sync_modification_date_fn() OWNER TO ginnastica_user;

--
-- TOC entry 202 (class 1259 OID 24749)
-- Name: apparatus_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE public.apparatus_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.apparatus_seq OWNER TO ginnastica_user;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 203 (class 1259 OID 24751)
-- Name: apparatus; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE public.apparatus (
    id integer DEFAULT nextval('public.apparatus_seq'::regclass) NOT NULL,
    name_it character varying(50) NOT NULL,
    name_en character varying(50) NOT NULL,
    gender character(1) NOT NULL,
    sequence integer NOT NULL
);


ALTER TABLE public.apparatus OWNER TO ginnastica_user;

--
-- TOC entry 204 (class 1259 OID 24755)
-- Name: athlete_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE public.athlete_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.athlete_seq OWNER TO ginnastica_user;

--
-- TOC entry 205 (class 1259 OID 24757)
-- Name: athlete; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE public.athlete (
    id integer DEFAULT nextval('public.athlete_seq'::regclass) NOT NULL,
    first_name character(50) NOT NULL,
    last_name character(50) NOT NULL,
    gender character(1) NOT NULL,
    nation_id integer NOT NULL
);


ALTER TABLE public.athlete OWNER TO ginnastica_user;

--
-- TOC entry 206 (class 1259 OID 24761)
-- Name: nations; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE public.nations (
    id integer NOT NULL,
    name text NOT NULL,
    nicename text NOT NULL,
    iso3 character(3),
    numcode integer,
    phonecode integer NOT NULL,
    iso character(2) NOT NULL,
    ioc character(3) DEFAULT '   '::bpchar NOT NULL
);


ALTER TABLE public.nations OWNER TO ginnastica_user;

--
-- TOC entry 207 (class 1259 OID 24768)
-- Name: athlete_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW public.athlete_vw AS
 SELECT athlete.id,
    athlete.first_name,
    athlete.last_name,
    athlete.gender,
    nations.nicename AS nation
   FROM (public.athlete
     LEFT JOIN public.nations ON ((athlete.nation_id = nations.id)));


ALTER TABLE public.athlete_vw OWNER TO ginnastica_user;

--
-- TOC entry 208 (class 1259 OID 24772)
-- Name: scores_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE public.scores_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.scores_seq OWNER TO ginnastica_user;

--
-- TOC entry 209 (class 1259 OID 24774)
-- Name: scores; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE public.scores (
    id integer DEFAULT nextval('public.scores_seq'::regclass) NOT NULL,
    sport_event_id integer NOT NULL,
    athlete_id integer NOT NULL,
    apparatus_id integer NOT NULL,
    difficulty_score real NOT NULL,
    final_score real NOT NULL,
    force_score integer DEFAULT 0 NOT NULL,
    final_apparatus boolean DEFAULT false NOT NULL,
    created timestamp without time zone DEFAULT now(),
    last_modified timestamp without time zone,
    penalty_score real DEFAULT 0 NOT NULL,
    execution_score real DEFAULT 0 NOT NULL
);


ALTER TABLE public.scores OWNER TO ginnastica_user;

--
-- TOC entry 210 (class 1259 OID 24781)
-- Name: sport_event_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE public.sport_event_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.sport_event_seq OWNER TO ginnastica_user;

--
-- TOC entry 211 (class 1259 OID 24783)
-- Name: sport_event; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE public.sport_event (
    id integer DEFAULT nextval('public.sport_event_seq'::regclass) NOT NULL,
    location_id integer NOT NULL,
    year date NOT NULL,
    name character varying(50) NOT NULL
);


ALTER TABLE public.sport_event OWNER TO ginnastica_user;

--
-- TOC entry 221 (class 1259 OID 32794)
-- Name: chrono_list_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW public.chrono_list_vw AS
 SELECT athlete.id,
    athlete.gender,
    (((athlete.first_name)::text || ' '::text) || (athlete.last_name)::text) AS fullname,
    ( SELECT nations_1.id
           FROM public.nations nations_1
          WHERE (nations_1.id = athlete.nation_id)) AS nation,
    apparatus.name_it AS apparatus,
    scores.difficulty_score,
    scores.execution_score,
    scores.penalty_score,
    scores.final_score,
    ( SELECT sum(scores_l.final_score) AS sum
           FROM public.scores scores_l
          WHERE (scores_l.athlete_id = athlete.id)
          GROUP BY scores_l.athlete_id) AS total_score,
    sport_event.id AS event_id,
    scores.last_modified
   FROM ((((public.scores
     LEFT JOIN public.athlete ON ((scores.athlete_id = athlete.id)))
     LEFT JOIN public.nations ON ((scores.athlete_id = athlete.nation_id)))
     LEFT JOIN public.apparatus ON ((scores.apparatus_id = apparatus.id)))
     LEFT JOIN public.sport_event ON ((scores.sport_event_id = sport_event.id)))
  ORDER BY scores.last_modified DESC;


ALTER TABLE public.chrono_list_vw OWNER TO ginnastica_user;

--
-- TOC entry 212 (class 1259 OID 24792)
-- Name: city_cup_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE public.city_cup_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.city_cup_seq OWNER TO ginnastica_user;

--
-- TOC entry 213 (class 1259 OID 24798)
-- Name: sport_event_subscriptions_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE public.sport_event_subscriptions_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.sport_event_subscriptions_seq OWNER TO ginnastica_user;

--
-- TOC entry 214 (class 1259 OID 24800)
-- Name: sport_event_subscriptions; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE public.sport_event_subscriptions (
    id integer DEFAULT nextval('public.sport_event_subscriptions_seq'::regclass) NOT NULL,
    athlete_id integer NOT NULL,
    sport_event_id integer NOT NULL,
    final_apparatus_id integer
);


ALTER TABLE public.sport_event_subscriptions OWNER TO ginnastica_user;

--
-- TOC entry 215 (class 1259 OID 24804)
-- Name: event_athlete_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW public.event_athlete_vw AS
 SELECT ses.sport_event_id,
    athlete.id,
    athlete.first_name,
    athlete.last_name,
    athlete.gender,
    athlete.nation_id
   FROM (public.sport_event_subscriptions ses
     LEFT JOIN public.athlete ON ((athlete.id = ses.athlete_id)))
  ORDER BY athlete.first_name;


ALTER TABLE public.event_athlete_vw OWNER TO ginnastica_user;

--
-- TOC entry 216 (class 1259 OID 24808)
-- Name: location_seq; Type: SEQUENCE; Schema: public; Owner: ginnastica_user
--

CREATE SEQUENCE public.location_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.location_seq OWNER TO ginnastica_user;

--
-- TOC entry 217 (class 1259 OID 24810)
-- Name: location; Type: TABLE; Schema: public; Owner: ginnastica_user
--

CREATE TABLE public.location (
    id integer DEFAULT nextval('public.location_seq'::regclass) NOT NULL,
    name character varying(50) NOT NULL,
    address text,
    city character varying(50),
    zip character varying(10),
    nation_id integer
);


ALTER TABLE public.location OWNER TO ginnastica_user;

--
-- TOC entry 220 (class 1259 OID 32789)
-- Name: ranking_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW public.ranking_vw AS
 SELECT ev.year,
    at.gender,
    at.first_name,
    at.last_name,
    n.ioc,
    array_agg(ap.name_it) AS apparatus,
    array_agg(s.final_score) AS final_scores,
    array_agg(s.difficulty_score) AS difficulty_scores,
    sum(s.final_score) AS total_final_score,
    sum(s.difficulty_score) AS total_difficulty_score
   FROM ((((public.scores s
     LEFT JOIN public.sport_event ev ON ((ev.id = s.sport_event_id)))
     LEFT JOIN public.athlete at ON ((at.id = s.athlete_id)))
     LEFT JOIN public.apparatus ap ON ((ap.id = s.apparatus_id)))
     LEFT JOIN public.nations n ON ((n.id = at.nation_id)))
  GROUP BY ev.year, at.gender, at.first_name, at.last_name, n.ioc, s.sport_event_id, s.athlete_id
  ORDER BY (sum(s.final_score)) DESC;


ALTER TABLE public.ranking_vw OWNER TO ginnastica_user;

--
-- TOC entry 219 (class 1259 OID 32784)
-- Name: scores_male_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW public.scores_male_vw AS
 SELECT athlete.id,
    athlete.first_name,
    athlete.last_name,
    ( SELECT nations_1.ioc
           FROM public.nations nations_1
          WHERE (nations_1.id = athlete.nation_id)) AS nation,
    apparatus.name_it AS apparatus,
    scores.difficulty_score,
    scores.final_score,
    sport_event.year
   FROM ((((public.scores
     LEFT JOIN public.athlete ON ((scores.athlete_id = athlete.id)))
     LEFT JOIN public.nations ON ((scores.athlete_id = athlete.nation_id)))
     LEFT JOIN public.apparatus ON ((scores.apparatus_id = apparatus.id)))
     LEFT JOIN public.sport_event ON ((scores.sport_event_id = sport_event.id)));


ALTER TABLE public.scores_male_vw OWNER TO ginnastica_user;

--
-- TOC entry 218 (class 1259 OID 32779)
-- Name: total_scores_vw; Type: VIEW; Schema: public; Owner: ginnastica_user
--

CREATE VIEW public.total_scores_vw AS
 SELECT s.sport_event_id,
    s.athlete_id,
    at.first_name,
    at.last_name,
    sum(s.final_score) AS total_final_score,
    sum(s.difficulty_score) AS total_difficulty_score
   FROM ((public.scores s
     LEFT JOIN public.sport_event ev ON ((ev.id = s.sport_event_id)))
     LEFT JOIN public.athlete at ON ((at.id = s.athlete_id)))
  GROUP BY s.sport_event_id, s.athlete_id, at.first_name, at.last_name
  ORDER BY at.first_name;


ALTER TABLE public.total_scores_vw OWNER TO ginnastica_user;

--
-- TOC entry 2919 (class 0 OID 24751)
-- Dependencies: 203
-- Data for Name: apparatus; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY public.apparatus (id, name_it, name_en, gender, sequence) FROM stdin;
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
-- TOC entry 2921 (class 0 OID 24757)
-- Dependencies: 205
-- Data for Name: athlete; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY public.athlete (id, first_name, last_name, gender, nation_id) FROM stdin;
48	Carina                                            	Kroell                                            	F	80
49	Marian                                            	Dragulescu                                        	M	176
23	Arthur Nory                                       	Mariano                                           	M	30
31	Eythora                                           	Thorsdottir                                       	F	150
32	Bart                                              	Deurloo                                           	M	150
33	Angelina                                          	Melnikova                                         	F	177
34	Nikita                                            	Ignatyev                                          	M	177
36	Oleg                                              	Verniaiev                                         	M	223
37	Igor                                              	Radivilov                                         	M	223
39	Caterina                                          	Barloggio                                         	F	206
40	Thea                                              	Brogli                                            	F	206
41	Ilaria                                            	Käslin                                            	F	206
42	Benjamin                                          	Gischard                                          	M	206
44	Paolo                                             	Principi                                          	M	105
35	Angelina                                          	Kysla                                             	F	223
38	J.B                                               	Lopez Arocha                                      	F	231
46	Victoria Kayen                                    	Woo                                               	F	38
47	René                                              	Cournoyer                                         	M	38
50	Marco                                             	Rizzo                                             	M	206
27	Lukas                                             	Dauser                                            	M	80
52	James                                             	Hall                                              	M	225
53	Marcel                                            	Nguyen                                            	M	80
54	Nikita                                            	Nagornyy                                          	M	177
55	Oliver                                            	Hegi                                              	M	206
56	Pablo                                             	Brägger                                           	M	206
57	Cory                                              	Paterson                                          	M	38
58	Julien                                            	Gobaux                                            	M	73
59	Diana                                             	Varinska                                          	F	223
60	Emily                                             	Thomas                                            	F	225
61	Isabela                                           	Onyshko                                           	F	38
62	Kim                                               	Bui                                               	F	80
63	Leonie                                            	Meier                                             	F	206
64	Mélanie                                           	De Jesus Dos Santos                               	F	73
65	Oksana                                            	Chusovitina                                       	F	229
67	Anina                                             	Wildi                                             	F	206
68	Jade                                              	Barbosa                                           	F	30
66	Flávia Lopez                                      	Saraiva                                           	F	30
73	Amhet                                             	Asil                                              	M	218
74	Joel                                              	Plata                                             	M	199
75	Kazuma                                            	Kaya                                              	M	107
76	Lorenzo                                           	Casali                                            	M	105
77	Paul                                              	Degouy                                            	M	73
79	Taha                                              	Serhani                                           	M	206
80	Vinzenz                                           	Höck                                              	M	14
81	Dominic                                           	Tamsel                                            	M	206
82	Illia                                             	Kovtun                                            	M	223
83	Alice                                             	D'Amato                                           	F	105
84	Chiaki                                            	Hatakeda                                          	F	107
85	Selina                                            	Kickinger                                         	F	14
86	Laura                                             	Casabuena                                         	F	199
87	Chiara                                            	Giubellini                                        	F	206
88	Bilge                                             	Tarhan                                            	F	218
89	Yuliia                                            	Kasianenko                                        	F	223
90	Adem                                              	Asil                                              	M	218
92	Lucas                                             	Desanges                                          	M	73
93	Yul                                               	Moldauer                                          	M	226
94	Morgane                                           	Osyssek-Reimer                                    	F	73
95	Casimir                                           	Schmidt                                           	M	150
96	Lorenzo Minh                                      	Casali                                            	M	105
97	Lena                                              	Bickel                                            	F	206
98	Valeriia                                          	Osipova                                           	F	223
99	Aydon                                             	Benas                                             	M	226
100	Caio                                              	Souza                                             	M	30
101	Félix                                             	Dolci                                             	M	38
102	Florian                                           	Langenegger                                       	M	206
103	Jermain                                           	Gruenberg                                         	M	150
104	Leo                                               	Saladino                                          	M	73
106	Matteo                                            	Giubellini                                        	M	206
107	Timo                                              	Eder                                              	M	80
108	Angela                                            	Andreoli                                          	F	105
109	Anny                                              	Wu                                                	F	206
110	Julia                                             	Soares                                            	F	30
111	Kalia                                             	Nemour                                            	F	3
112	Marlene                                           	Gotthardt                                         	F	80
114	Naomi                                             	Visser                                            	F	150
115	Stefanie                                          	Siegenthaler                                      	F	206
116	Veronica                                          	Mandriota                                         	F	105
117	Mario                                             	Macchiati                                         	M	105
118	Karina                                            	Schoenmaier                                       	F	80
119	Jan                                               	Imhof                                             	M	206
120	Kaylia                                            	Nemour                                            	F	3
\.


--
-- TOC entry 2931 (class 0 OID 24810)
-- Dependencies: 217
-- Data for Name: location; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY public.location (id, name, address, city, zip, nation_id) FROM stdin;
1	Chiasso		Chiasso	6830	206
\.


--
-- TOC entry 2922 (class 0 OID 24761)
-- Dependencies: 206
-- Data for Name: nations; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY public.nations (id, name, nicename, iso3, numcode, phonecode, iso, ioc) FROM stdin;
7	ANGUILLA	Anguilla	AIA	660	1264	AI	   
69	FALKLAND ISLANDS (MALVINAS)	Falkland Islands (Malvinas)	FLK	238	500	FK	   
70	FAROE ISLANDS	Faroe Islands	FRO	234	298	FO	   
74	FRENCH GUIANA	French Guiana	GUF	254	594	GF	   
75	FRENCH POLYNESIA	French Polynesia	PYF	258	689	PF	   
82	GIBRALTAR	Gibraltar	GIB	292	350	GI	   
84	GREENLAND	Greenland	GRL	304	299	GL	   
86	GUADELOUPE	Guadeloupe	GLP	312	590	GP	   
2	ALBANIA	Albania	ALB	8	355	AL	ALB
3	ALGERIA	Algeria	DZA	12	213	DZ	ALG
5	ANDORRA	Andorra	AND	20	376	AD	AND
6	ANGOLA	Angola	AGO	24	244	AO	ANG
10	ARGENTINA	Argentina	ARG	32	54	AR	ARG
11	ARMENIA	Armenia	ARM	51	374	AM	ARM
12	ARUBA	Aruba	ABW	533	297	AW	ARU
13	AUSTRALIA	Australia	AUS	36	61	AU	AUS
14	AUSTRIA	Austria	AUT	40	43	AT	AUT
15	AZERBAIJAN	Azerbaijan	AZE	31	994	AZ	AZE
16	BAHAMAS	Bahamas	BHS	44	1242	BS	BAH
18	BANGLADESH	Bangladesh	BGD	50	880	BD	BAN
19	BARBADOS	Barbados	BRB	52	1246	BB	BAR
35	BURUNDI	Burundi	BDI	108	257	BI	BDI
20	BELARUS	Belarus	BLR	112	375	BY	BLR
21	BELGIUM	Belgium	BEL	56	32	BE	BEL
22	BELIZE	Belize	BLZ	84	501	BZ	BIZ
23	BENIN	Benin	BEN	204	229	BJ	BEN
25	BHUTAN	Bhutan	BTN	64	975	BT	BHU
26	BOLIVIA	Bolivia	BOL	68	591	BO	BOL
27	BOSNIA AND HERZEGOVINA	Bosnia and Herzegovina	BIH	70	387	BA	BIH
28	BOTSWANA	Botswana	BWA	72	267	BW	BOT
30	BRAZIL	Brazil	BRA	76	55	BR	BRA
32	BRUNEI DARUSSALAM	Brunei Darussalam	BRN	96	673	BN	BRU
33	BULGARIA	Bulgaria	BGR	100	359	BG	BUL
34	BURKINA FASO	Burkina Faso	BFA	854	226	BF	BUR
36	CAMBODIA	Cambodia	KHM	116	855	KH	CAM
37	CAMEROON	Cameroon	CMR	120	237	CM	CMR
38	CANADA	Canada	CAN	124	1	CA	CAN
39	CAPE VERDE	Cape Verde	CPV	132	238	CV	CPV
41	CENTRAL AFRICAN REPUBLIC	Central African Republic	CAF	140	236	CF	CAF
42	CHAD	Chad	TCD	148	235	TD	CHA
43	CHILE	Chile	CHL	152	56	CL	CHI
44	CHINA	China	CHN	156	86	CN	CHN
47	COLOMBIA	Colombia	COL	170	57	CO	COL
48	COMOROS	Comoros	COM	174	269	KM	COM
49	CONGO	Congo	COG	178	242	CG	CGO
62	ECUADOR	Ecuador	ECU	218	593	EC	ECU
51	COOK ISLANDS	Cook Islands	COK	184	682	CK	COK
52	COSTA RICA	Costa Rica	CRI	188	506	CR	CRC
54	CROATIA	Croatia	HRV	191	385	HR	CRO
55	CUBA	Cuba	CUB	192	53	CU	CUB
57	CZECH REPUBLIC	Czech Republic	CZE	203	420	CZ	CZE
53	COTE D'IVOIRE	Cote D'Ivoire	CIV	384	225	CI	CIV
56	CYPRUS	Cyprus	CYP	196	357	CY	CYP
58	DENMARK	Denmark	DNK	208	45	DK	DEN
59	DJIBOUTI	Djibouti	DJI	262	253	DJ	DJI
60	DOMINICA	Dominica	DMA	212	1767	DM	DMA
50	CONGO, THE DEMOCRATIC REPUBLIC OF THE	Congo, the Democratic Republic of the	COD	180	242	CD	COD
63	EGYPT	Egypt	EGY	818	20	EG	EGY
64	EL SALVADOR	El Salvador	SLV	222	503	SV	ESA
65	EQUATORIAL GUINEA	Equatorial Guinea	GNQ	226	240	GQ	GEQ
66	ERITREA	Eritrea	ERI	232	291	ER	ERI
67	ESTONIA	Estonia	EST	233	372	EE	EST
68	ETHIOPIA	Ethiopia	ETH	231	251	ET	ETH
71	FIJI	Fiji	FJI	242	679	FJ	FIG
72	FINLAND	Finland	FIN	246	358	FI	FIN
73	FRANCE	France	FRA	250	33	FR	FRA
77	GABON	Gabon	GAB	266	241	GA	GAB
79	GEORGIA	Georgia	GEO	268	995	GE	GEO
80	GERMANY	Germany	DEU	276	49	DE	GER
81	GHANA	Ghana	GHA	288	233	GH	GHA
83	GREECE	Greece	GRC	300	30	GR	GRE
85	GRENADA	Grenada	GRD	308	1473	GD	GRN
87	GUAM	Guam	GUM	316	1671	GU	GUM
88	GUATEMALA	Guatemala	GTM	320	502	GT	GUA
89	GUINEA	Guinea	GIN	324	224	GN	GUI
90	GUINEA-BISSAU	Guinea-Bissau	GNB	624	245	GW	GBS
91	GUYANA	Guyana	GUY	328	592	GY	GUY
92	HAITI	Haiti	HTI	332	509	HT	HAI
95	HONDURAS	Honduras	HND	340	504	HN	HON
96	HONG KONG	Hong Kong	HKG	344	852	HK	HKG
97	HUNGARY	Hungary	HUN	348	36	HU	HUN
98	ICELAND	Iceland	ISL	352	354	IS	ISL
99	INDIA	India	IND	356	91	IN	IND
9	ANTIGUA AND BARBUDA	Antigua and Barbuda	ATG	28	1268	AG	ANT
102	IRAQ	Iraq	IRQ	368	964	IQ	IRQ
103	IRELAND	Ireland	IRL	372	353	IE	IRL
104	ISRAEL	Israel	ISR	376	972	IL	ISR
105	ITALY	Italy	ITA	380	39	IT	ITA
106	JAMAICA	Jamaica	JAM	388	1876	JM	JAM
101	IRAN	Iran	IRN	364	98	IR	IRI
17	BAHRAIN	Bahrain	BHR	48	973	BH	BRN
78	GAMBIA	Gambia	GMB	270	220	GM	GAM
125	MACAO	Macao	MAC	446	853	MO	   
134	MARTINIQUE	Martinique	MTQ	474	596	MQ	   
137	MAYOTTE	Mayotte	\N	\N	269	YT	   
143	MONTSERRAT	Montserrat	MSR	500	1664	MS	   
151	NETHERLANDS ANTILLES	Netherlands Antilles	ANT	530	599	AN	   
152	NEW CALEDONIA	New Caledonia	NCL	540	687	NC	   
157	NIUE	Niue	NIU	570	683	NU	   
158	NORFOLK ISLAND	Norfolk Island	NFK	574	672	NF	   
159	NORTHERN MARIANA ISLANDS	Northern Mariana Islands	MNP	580	1670	MP	   
175	REUNION	Reunion	REU	638	262	RE	   
179	SAINT HELENA	Saint Helena	SHN	654	290	SH	   
182	SAINT PIERRE AND MIQUELON	Saint Pierre and Miquelon	SPM	666	508	PM	   
203	SVALBARD AND JAN MAYEN	Svalbard and Jan Mayen	SJM	744	47	SJ	   
107	JAPAN	Japan	JPN	392	81	JP	JPN
109	KAZAKHSTAN	Kazakhstan	KAZ	398	7	KZ	KAZ
108	JORDAN	Jordan	JOR	400	962	JO	JOR
110	KENYA	Kenya	KEN	404	254	KE	KEN
111	KIRIBATI	Kiribati	KIR	296	686	KI	KIR
114	KUWAIT	Kuwait	KWT	414	965	KW	KUW
115	KYRGYZSTAN	Kyrgyzstan	KGZ	417	996	KG	KGZ
116	LAO PEOPLE'S DEMOCRATIC REPUBLIC	Lao People's Democratic Republic	LAO	418	856	LA	LAO
117	LATVIA	Latvia	LVA	428	371	LV	LAT
118	LEBANON	Lebanon	LBN	422	961	LB	LIB
119	LESOTHO	Lesotho	LSO	426	266	LS	LES
120	LIBERIA	Liberia	LBR	430	231	LR	LBR
121	LIBYAN ARAB JAMAHIRIYA	Libyan Arab Jamahiriya	LBY	434	218	LY	LBA
122	LIECHTENSTEIN	Liechtenstein	LIE	438	423	LI	LIE
123	LITHUANIA	Lithuania	LTU	440	370	LT	LTU
124	LUXEMBOURG	Luxembourg	LUX	442	352	LU	LUX
127	MADAGASCAR	Madagascar	MDG	450	261	MG	MAD
128	MALAWI	Malawi	MWI	454	265	MW	MAW
129	MALAYSIA	Malaysia	MYS	458	60	MY	MAS
130	MALDIVES	Maldives	MDV	462	960	MV	MDV
131	MALI	Mali	MLI	466	223	ML	MLI
132	MALTA	Malta	MLT	470	356	MT	MLT
133	MARSHALL ISLANDS	Marshall Islands	MHL	584	692	MH	MHL
135	MAURITANIA	Mauritania	MRT	478	222	MR	MTN
136	MAURITIUS	Mauritius	MUS	480	230	MU	MRI
140	MOLDOVA, REPUBLIC OF	Moldova, Republic of	MDA	498	373	MD	MDA
138	MEXICO	Mexico	MEX	484	52	MX	MEX
141	MONACO	Monaco	MCO	492	377	MC	MON
142	MONGOLIA	Mongolia	MNG	496	976	MN	MGL
144	MOROCCO	Morocco	MAR	504	212	MA	MAR
145	MOZAMBIQUE	Mozambique	MOZ	508	258	MZ	MOZ
146	MYANMAR	Myanmar	MMR	104	95	MM	MYA
147	NAMIBIA	Namibia	NAM	516	264	NA	NAM
148	NAURU	Nauru	NRU	520	674	NR	NRU
149	NEPAL	Nepal	NPL	524	977	NP	NEP
150	NETHERLANDS	Netherlands	NLD	528	31	NL	NED
153	NEW ZEALAND	New Zealand	NZL	554	64	NZ	NZL
154	NICARAGUA	Nicaragua	NIC	558	505	NI	NCA
155	NIGER	Niger	NER	562	227	NE	NIG
156	NIGERIA	Nigeria	NGA	566	234	NG	NGR
160	NORWAY	Norway	NOR	578	47	NO	NOR
161	OMAN	Oman	OMN	512	968	OM	OMA
162	PAKISTAN	Pakistan	PAK	586	92	PK	PAK
163	PALAU	Palau	PLW	585	680	PW	PLW
165	PANAMA	Panama	PAN	591	507	PA	PAN
164	PALESTINE	Plestine	\N	\N	970	PS	PLE
166	PAPUA NEW GUINEA	Papua New Guinea	PNG	598	675	PG	PNG
167	PARAGUAY	Paraguay	PRY	600	595	PY	PAR
168	PERU	Peru	PER	604	51	PE	PER
169	PHILIPPINES	Philippines	PHL	608	63	PH	PHI
171	POLAND	Poland	POL	616	48	PL	POL
172	PORTUGAL	Portugal	PRT	620	351	PT	POR
173	PUERTO RICO	Puerto Rico	PRI	630	1787	PR	PUR
174	QATAR	Qatar	QAT	634	974	QA	QAT
176	ROMANIA	Romania	ROM	642	40	RO	ROU
177	RUSSIAN FEDERATION	Russian Federation	RUS	643	70	RU	RUS
178	RWANDA	Rwanda	RWA	646	250	RW	RWA
180	SAINT KITTS AND NEVIS	Saint Kitts and Nevis	KNA	659	1869	KN	SKN
181	SAINT LUCIA	Saint Lucia	LCA	662	1758	LC	LCA
183	SAINT VINCENT AND THE GRENADINES	Saint Vincent and the Grenadines	VCT	670	1784	VC	VIN
184	SAMOA	Samoa	WSM	882	684	WS	SAM
185	SAN MARINO	San Marino	SMR	674	378	SM	SMR
187	SAUDI ARABIA	Saudi Arabia	SAU	682	966	SA	KSA
188	SENEGAL	Senegal	SEN	686	221	SN	SEN
190	SEYCHELLES	Seychelles	SYC	690	248	SC	SEY
191	SIERRA LEONE	Sierra Leone	SLE	694	232	SL	SLE
192	SINGAPORE	Singapore	SGP	702	65	SG	SGP
193	SLOVAKIA	Slovakia	SVK	703	421	SK	SVK
194	SLOVENIA	Slovenia	SVN	705	386	SI	SLO
195	SOLOMON ISLANDS	Solomon Islands	SLB	90	677	SB	SOL
196	SOMALIA	Somalia	SOM	706	252	SO	SOM
197	SOUTH AFRICA	South Africa	ZAF	710	27	ZA	RSA
113	KOREA, REPUBLIC OF	Korea, Republic of	KOR	410	82	KR	KOR
199	SPAIN	Spain	ESP	724	34	ES	ESP
200	SRI LANKA	Sri Lanka	LKA	144	94	LK	SRI
201	SUDAN	Sudan	SDN	736	249	SD	SUD
202	SURINAME	Suriname	SUR	740	597	SR	SUR
186	SAO TOME AND PRINCIPE	Sao Tome and Principe	STP	678	239	ST	STP
204	SWAZILAND	Swaziland	SWZ	748	268	SZ	SWZ
205	SWEDEN	Sweden	SWE	752	46	SE	SWE
207	SYRIAN ARAB REPUBLIC	Syrian Arab Republic	SYR	760	963	SY	SYR
139	MICRONESIA, FEDERATED STATES OF	Micronesia, Federated States of	FSM	583	691	FM	FSM
189	SERBIA	Serbia	\N	\N	381	CS	SRB
214	TOKELAU	Tokelau	TKL	772	690	TK	   
220	TURKS AND CAICOS ISLANDS	Turks and Caicos Islands	TCA	796	1649	TC	   
235	WALLIS AND FUTUNA	Wallis and Futuna	WLF	876	681	WF	   
236	WESTERN SAHARA	Western Sahara	ESH	732	212	EH	   
206	SWITZERLAND	Switzerland	CHE	756	41	CH	SUI
1	AFGHANISTAN	Afghanistan	AFG	4	93	AF	AFG
24	BERMUDA	Bermuda	BMU	60	1441	BM	BER
40	CAYMAN ISLANDS	Cayman Islands	CYM	136	1345	KY	CAY
208	TAIWAN, PROVINCE OF CHINA	Taiwan, Province of China	TWN	158	886	TW	TWN
61	DOMINICAN REPUBLIC	Dominican Republic	DOM	214	1809	DO	DOM
100	INDONESIA	Indonesia	IDN	360	62	ID	INA
126	MACEDONIA, THE FORMER YUGOSLAV REPUBLIC OF	Macedonia, the Former Yugoslav Republic of	MKD	807	389	MK	MKD
112	KOREA, DEMOCRATIC PEOPLE'S REPUBLIC OF	Korea, Democratic People's Republic of	PRK	408	850	KP	PRK
209	TAJIKISTAN	Tajikistan	TJK	762	992	TJ	TJK
210	TANZANIA, UNITED REPUBLIC OF	Tanzania, United Republic of	TZA	834	255	TZ	TAN
211	THAILAND	Thailand	THA	764	66	TH	THA
212	TIMOR-LESTE	Timor-Leste	\N	\N	670	TL	TLS
213	TOGO	Togo	TGO	768	228	TG	TOG
215	TONGA	Tonga	TON	776	676	TO	TGA
216	TRINIDAD AND TOBAGO	Trinidad and Tobago	TTO	780	1868	TT	TTO
217	TUNISIA	Tunisia	TUN	788	216	TN	TUN
218	TURKEY	Turkey	TUR	792	90	TR	TUR
219	TURKMENISTAN	Turkmenistan	TKM	795	7370	TM	TKM
221	TUVALU	Tuvalu	TUV	798	688	TV	TUV
222	UGANDA	Uganda	UGA	800	256	UG	UGA
223	UKRAINE	Ukraine	UKR	804	380	UA	UKR
224	UNITED ARAB EMIRATES	United Arab Emirates	ARE	784	971	AE	UAE
225	UNITED KINGDOM	United Kingdom	GBR	826	44	GB	GBR
226	UNITED STATES	United States	USA	840	1	US	USA
228	URUGUAY	Uruguay	URY	858	598	UY	URU
229	UZBEKISTAN	Uzbekistan	UZB	860	998	UZ	UZB
230	VANUATU	Vanuatu	VUT	548	678	VU	VAN
231	VENEZUELA	Venezuela	VEN	862	58	VE	VEN
232	VIET NAM	Viet Nam	VNM	704	84	VN	VIE
233	VIRGIN ISLANDS	Virgin Islands	VGB	92	1284	VG	ISV
237	YEMEN	Yemen	YEM	887	967	YE	YEM
238	ZAMBIA	Zambia	ZMB	894	260	ZM	ZAM
239	ZIMBABWE	Zimbabwe	ZWE	716	263	ZW	ZIM
240	MONTENEGRO	Montenegro	   	\N	0	  	MNE
\.


--
-- TOC entry 2924 (class 0 OID 24774)
-- Dependencies: 209
-- Data for Name: scores; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY public.scores (id, sport_event_id, athlete_id, apparatus_id, difficulty_score, final_score, force_score, final_apparatus, created, last_modified, penalty_score, execution_score) FROM stdin;
169	1	35	7	5	13.75	0	f	2018-10-01 16:02:02.047387	\N	0	0
170	1	50	1	5.9	14.85	0	f	2018-10-01 16:02:02.047387	\N	0	0
171	1	39	9	5.3	13.8	0	f	2018-10-01 16:02:02.047387	\N	0	0
172	1	34	1	6.1	13.5	0	f	2018-10-01 16:02:02.047387	\N	0	0
173	1	40	7	5	12.4	0	f	2018-10-01 16:02:02.047387	\N	0	0
174	1	23	1	6.4	14.15	0	f	2018-10-01 16:02:02.047387	\N	0	0
175	1	31	7	4	12.75	0	f	2018-10-01 16:02:02.047387	\N	0	0
176	1	32	1	6.2	14.1	0	f	2018-10-01 16:02:02.047387	\N	0	0
177	1	48	7	4.8	13.4	0	f	2018-10-01 16:02:02.047387	\N	0	0
178	1	47	1	5.8	14.25	0	f	2018-10-01 16:02:02.047387	\N	0	0
179	1	37	1	5.8	13.15	0	f	2018-10-01 16:02:02.047387	\N	0	0
180	1	38	8	6.1	14.35	0	f	2018-10-01 16:02:02.047387	\N	0	0
181	1	49	1	6.3	14.5	0	f	2018-10-01 16:02:02.047387	\N	0	0
182	1	41	7	5	13.45	0	f	2018-10-01 16:02:02.047387	\N	0	0
183	1	36	2	6.9	14.45	0	f	2018-10-01 16:02:02.047387	\N	0	0
184	1	46	8	5.4	12.45	0	f	2018-10-01 16:02:02.047387	\N	0	0
185	1	42	1	6.1	14.3	0	f	2018-10-01 16:02:02.047387	\N	0	0
186	1	33	7	5.8	14.9	0	f	2018-10-01 16:02:02.047387	\N	0	0
187	1	27	4	5.2	14.4	0	f	2018-10-01 16:02:02.047387	\N	0	0
188	1	50	2	5.7	13.25	0	f	2018-10-01 16:02:02.047387	\N	0	0
189	1	34	4	5.6	13.55	0	f	2018-10-01 16:02:02.047387	\N	0	0
190	1	23	4	5.2	14.45	0	f	2018-10-01 16:02:02.047387	\N	0	0
191	1	32	4	5.6	14.95	0	f	2018-10-01 16:02:02.047387	\N	0	0
192	1	47	3	5.6	14.15	0	f	2018-10-01 16:02:02.047387	\N	0	0
194	1	37	3	6.8	15.4	0	f	2018-10-01 16:02:02.047387	\N	0	0
193	1	49	3	0	0	0	f	2018-10-01 16:02:02.047387	\N	0	0
195	1	49	4	6	15	0	f	2018-10-01 16:02:02.047387	\N	0	0
196	1	36	3	6.6	14.85	0	f	2018-10-01 16:02:02.047387	\N	0	0
197	1	42	3	5.8	14.35	0	f	2018-10-01 16:02:02.047387	\N	0	0
198	1	27	5	6.7	14.25	0	f	2018-10-01 16:02:02.047387	\N	0	0
199	1	44	2	6.6	13.85	0	f	2018-10-01 16:02:02.047387	\N	0	0
200	1	34	5	6.2	14.55	0	f	2018-10-01 16:02:02.047387	\N	0	0
201	1	39	10	5	13.05	0	f	2018-10-01 16:02:02.047387	\N	0	0
202	1	23	6	6.3	13.9	0	f	2018-10-01 16:02:02.047387	\N	0	0
203	1	40	10	4.9	12.1	0	f	2018-10-01 16:02:02.047387	\N	0	0
204	1	32	6	6.4	14.55	0	f	2018-10-01 16:02:02.047387	\N	0	0
205	1	31	10	5.8	14	0	f	2018-10-01 16:02:02.047387	\N	0	0
206	1	47	5	5.7	14.05	0	f	2018-10-01 16:02:02.047387	\N	0	0
207	1	37	4	6	15.15	0	f	2018-10-01 16:02:02.047387	\N	0	0
208	1	48	10	5.4	13.55	0	f	2018-10-01 16:02:02.047387	\N	0	0
209	1	38	10	5.2	13.7	0	f	2018-10-01 16:02:02.047387	\N	0	0
210	1	49	5	5.3	13.05	0	f	2018-10-01 16:02:02.047387	\N	0	0
211	1	36	4	6	15.35	0	f	2018-10-01 16:02:02.047387	\N	0	0
212	1	42	4	5.6	15.05	0	f	2018-10-01 16:02:02.047387	\N	0	0
213	1	41	9	5.4	12.85	0	f	2018-10-01 16:02:02.047387	\N	0	0
214	1	46	10	5.1	13.2	0	f	2018-10-01 16:02:02.047387	\N	0	0
215	1	27	6	5.6	13.5	0	f	2018-10-01 16:02:02.047387	\N	0	0
216	1	44	4	5.2	13.25	0	f	2018-10-01 16:02:02.047387	\N	0	0
217	1	33	9	5.8	13.15	0	f	2018-10-01 16:02:02.047387	\N	0	0
218	1	50	3	6	14.65	0	f	2018-10-01 16:02:02.047387	\N	0	0
219	1	35	10	5.6	12.45	0	f	2018-10-01 16:02:02.047387	\N	0	0
220	1	49	2	5.3	13.65	0	t	2018-10-01 16:02:02.047387	\N	0	0
221	1	50	4	5.6	13.2	0	t	2018-10-01 16:02:02.047387	\N	0	0
222	1	41	10	5.4	12.9	0	t	2018-10-01 16:02:02.047387	\N	0	0
223	1	32	2	6.2	14.1	0	t	2018-10-01 16:02:02.047387	\N	0	0
224	1	31	9	5.7	14.2	0	t	2018-10-01 16:02:02.047387	\N	0	0
225	1	39	8	5.2	12.55	0	t	2018-10-01 16:02:02.047387	\N	0	0
226	1	37	6	5.7	13.35	0	t	2018-10-01 16:02:02.047387	\N	0	0
227	1	48	9	5.1	12.25	0	t	2018-10-01 16:02:02.047387	\N	0	0
228	1	42	2	5.5	11.9	0	t	2018-10-01 16:02:02.047387	\N	0	0
229	1	38	9	5.4	12.65	0	t	2018-10-01 16:02:02.047387	\N	0	0
230	1	36	5	7.2	16.15	0	t	2018-10-01 16:02:02.047387	\N	0	0
231	1	33	8	6.3	14.75	0	t	2018-10-01 16:02:02.047387	\N	0	0
332	2	53	1	5.9	13.95	0	f	2018-11-14 20:35:39.325002	2018-11-14 20:35:39.325002	0	0
168	1	44	1	5.8	13.9	0	f	2018-10-01 16:02:02.047387	2018-11-08 21:27:13.2117	0	0
333	2	32	1	5.5	14	0	f	2018-11-14 20:38:03.497322	2018-11-14 20:38:03.497322	0	0
335	2	23	1	5.6	13.85	0	f	2018-11-14 20:40:59.329371	2018-11-14 20:40:59.329371	0	0
338	2	54	1	6.4	13.85	0	f	2018-11-14 20:45:49.170098	2018-11-14 20:45:49.170098	0	0
319	2	41	7	4.6	13.6	0	f	2018-11-14 20:10:45.771403	2018-11-14 20:10:45.771403	0	0
321	2	64	8	6	12.1	0	f	2018-11-14 20:14:59.6904	2018-11-14 20:14:59.6904	0	0
323	2	66	9	5.6	12.35	0	f	2018-11-14 20:19:30.011326	2018-11-14 20:19:30.011326	0	0
325	2	33	8	6	13.25	0	f	2018-11-14 20:23:03.382171	2018-11-14 20:23:03.382171	0	0
327	2	68	7	5.4	14.25	0	f	2018-11-14 20:24:42.219387	2018-11-14 20:24:42.219387	0	0
339	2	55	2	5.3	12.85	0	f	2018-11-14 20:47:10.045895	2018-11-14 20:47:10.045895	0	0
340	2	49	4	5	14.5	0	f	2018-11-14 20:53:31.055816	2018-11-14 20:53:31.055816	0	0
341	2	58	4	4.8	13.95	0	f	2018-11-14 20:54:38.843237	2018-11-14 20:54:38.843237	0	0
382	2	53	4	5.2	14.6	0	t	2018-11-14 22:29:40.572896	2018-11-14 22:29:40.572896	0	0
342	2	56	4	4.8	14.05	0	f	2018-11-14 20:55:38.932782	2018-11-14 20:57:22.646626	0	0
343	2	57	5	5.5	13.45	0	f	2018-11-14 20:58:26.940311	2018-11-14 20:58:26.940311	0	0
344	2	53	3	5.6	14.2	0	f	2018-11-14 21:01:52.336588	2018-11-14 21:01:52.336588	0	0
345	2	32	4	5.2	13.7	0	f	2018-11-14 21:02:18.933903	2018-11-14 21:02:18.933903	0	0
346	2	23	4	4.8	13.4	0	f	2018-11-14 21:03:47.824018	2018-11-14 21:03:47.824018	0	0
347	2	54	3	6	14.85	0	f	2018-11-14 21:05:32.881554	2018-11-14 21:05:32.881554	0	0
348	2	55	5	5.8	14.75	0	f	2018-11-14 21:07:31.954866	2018-11-14 21:07:31.954866	0	0
350	2	58	5	5.6	14.25	0	f	2018-11-14 21:19:57.254696	2018-11-14 21:19:57.254696	0	0
353	2	56	5	5.9	14.1	0	f	2018-11-14 21:24:33.336057	2018-11-14 21:24:33.336057	0	0
355	2	57	6	5.7	13.65	0	f	2018-11-14 21:28:23.736836	2018-11-14 21:28:23.736836	0	0
357	2	53	5	5.9	14.5	0	f	2018-11-14 21:31:51.524621	2018-11-14 21:31:51.524621	0	0
359	2	32	6	6	12.5	0	f	2018-11-14 21:35:27.543049	2018-11-14 21:35:27.543049	0	0
362	2	23	6	5.4	11.45	0	f	2018-11-14 21:45:29.549127	2018-11-14 21:45:29.549127	0	0
363	2	54	5	5.9	13.3	0	f	2018-11-14 21:51:03.304662	2018-11-14 21:51:03.304662	0	0
366	2	55	6	5.8	14.3	0	f	2018-11-14 21:55:11.368919	2018-11-14 21:55:11.368919	0	0
368	2	36	4	5.6	13.15	0	f	2018-11-14 21:57:27.580082	2018-11-14 21:57:27.580082	0	0
369	2	49	5	4.9	13.3	0	f	2018-11-14 22:01:30.233355	2018-11-14 22:01:30.233355	0	0
372	2	49	2	4.3	11.6	0	t	2018-11-14 22:13:51.953705	2018-11-14 22:13:51.953705	0	0
374	2	56	6	5.9	13.65	0	t	2018-11-14 22:17:26.625506	2018-11-14 22:17:26.625506	0	0
376	2	58	3	5.4	13.9	0	t	2018-11-14 22:19:06.949072	2018-11-14 22:19:06.949072	0	0
377	2	55	4	4.8	14.05	0	t	2018-11-14 22:21:36.244425	2018-11-14 22:21:36.244425	0	0
379	2	54	4	5.6	14.6	0	t	2018-11-14 22:25:50.393622	2018-11-14 22:25:50.393622	0	0
349	2	36	3	5.8	12.4001	0	f	2018-11-14 21:10:28.907324	2018-11-14 22:56:00.495742	0	0
320	2	36	2	6.5	14.65	0	f	2018-11-14 20:11:53.65708	2018-11-14 20:11:53.65708	0	0
322	2	49	1	5.6	13.75	0	f	2018-11-14 20:16:44.971918	2018-11-14 20:16:44.971918	0	0
324	2	58	1	5.7	13.7	0	f	2018-11-14 20:20:32.94066	2018-11-14 20:20:32.94066	0	0
326	2	56	1	5.8	13.5	0	f	2018-11-14 20:23:48.098456	2018-11-14 20:23:48.098456	0	0
328	2	57	4	4.8	14.05	0	f	2018-11-14 20:25:57.997865	2018-11-14 20:25:57.997865	0	0
329	2	62	7	4.6	13.65	0	f	2018-11-14 20:27:13.155712	2018-11-14 20:27:13.155712	0	0
330	2	67	7	4.6	13.45	0	f	2018-11-14 20:33:14.463929	2018-11-14 20:33:14.463929	0	0
331	2	59	7	5	13.85	0	f	2018-11-14 20:35:36.303549	2018-11-14 20:35:36.303549	0	0
334	2	65	7	5.4	14.55	0	f	2018-11-14 20:39:13.10795	2018-11-14 20:39:13.10795	0	0
336	2	39	8	4.7	11.3	0	f	2018-11-14 20:43:53.371927	2018-11-14 20:43:53.371927	0	0
337	2	31	7	4.6	13.3	0	f	2018-11-14 20:45:04.148685	2018-11-14 20:45:04.148685	0	0
351	2	64	9	5.7	11.25	0	f	2018-11-14 21:21:16.815219	2018-11-14 21:21:16.815219	0	0
352	2	66	10	5.5	13.95	0	f	2018-11-14 21:22:47.23645	2018-11-14 21:22:47.23645	0	0
354	2	33	10	5.3	12.95	0	f	2018-11-14 21:27:09.229512	2018-11-14 21:27:09.229512	0	0
356	2	68	8	5.8	13.55	0	f	2018-11-14 21:30:07.367883	2018-11-14 21:30:07.367883	0	0
358	2	62	8	5.8	12.55	0	f	2018-11-14 21:34:11.199383	2018-11-14 21:34:11.199383	0	0
360	2	67	10	4.4	11.85	0	f	2018-11-14 21:37:32.07665	2018-11-14 21:37:32.07665	0	0
361	2	59	8	5.9	12.95	0	f	2018-11-14 21:45:04.573702	2018-11-14 21:45:04.573702	0	0
364	2	65	10	4	11.2	0	f	2018-11-14 21:52:42.141748	2018-11-14 21:52:42.141748	0	0
365	2	39	9	4.4	12	0	f	2018-11-14 21:54:33.244207	2018-11-14 21:54:33.244207	0	0
367	2	31	8	4.8	13.25	0	f	2018-11-14 21:56:53.689411	2018-11-14 21:56:53.689411	0	0
370	2	41	9	4.9	11.8	0	f	2018-11-14 22:01:38.013092	2018-11-14 22:01:38.013092	0	0
371	2	33	7	5.4	13.05	0	t	2018-11-14 22:12:43.206722	2018-11-14 22:12:43.206722	0	0
373	2	62	10	4.9	12.9	0	t	2018-11-14 22:16:23.817486	2018-11-14 22:16:23.817486	0	0
375	2	66	7	5.4	14.35	0	t	2018-11-14 22:18:02.862164	2018-11-14 22:18:02.862164	0	0
378	2	31	10	4.9	13.4	0	t	2018-11-14 22:22:00.929715	2018-11-14 22:22:00.929715	0	0
380	2	59	10	4.9	11.75	0	t	2018-11-14 22:26:07.777337	2018-11-14 22:26:07.777337	0	0
381	2	68	10	5.3	13.6	0	t	2018-11-14 22:29:39.498864	2018-11-14 22:29:39.498864	0	0
593	4	120	9	5.9	13.75	0	f	2024-11-06 21:29:28.068624	2024-11-06 21:29:28.068624	0	7.85
595	4	110	10	5.4	13.35	0	f	2024-11-06 21:38:08.099847	2024-11-06 21:38:08.099847	0	7.95
597	4	94	10	4.7	11.05	0	f	2024-11-06 21:42:04.879008	2024-11-06 21:42:04.879008	-0.1	6.45
599	4	115	10	4.4	10.6	0	f	2024-11-06 21:45:05.504943	2024-11-06 21:45:05.504943	-0.3	6.5
601	4	114	9	4.9	12.75	0	f	2024-11-06 21:48:21.443329	2024-11-06 21:48:21.443329	-0.1	7.95
603	4	108	10	3	6	0	f	2024-11-06 21:52:52.840213	2024-11-06 21:52:52.840213	-4	7
605	4	114	10	4.8	12.8	0	f	2024-11-06 22:04:55.479026	2024-11-06 22:04:55.479026	0	8
607	4	116	9	5	12.2	0	f	2024-11-06 22:08:27.08088	2024-11-06 22:08:27.08088	0	7.2
609	4	85	10	4.6	12.3	0	f	2024-11-06 22:11:43.97655	2024-11-06 22:11:43.97655	0	7.7
611	4	110	7	4.2	12.8	0	f	2024-11-06 22:14:07.490574	2024-11-06 22:14:07.490574	0	8.6
486	3	80	6	4.6	12.2	0	f	2022-11-23 21:58:10.641961	2022-11-23 21:58:10.641961	0	7.6
435	3	88	7	4.2	12.95	0	f	2022-11-23 20:10:48.041994	2022-11-23 20:10:48.041994	0	8.75
436	3	80	3	6	14.3	0	f	2022-11-23 20:12:38.656661	2022-11-23 20:12:38.656661	0	8.3
437	3	85	7	4.2	13	0	f	2022-11-23 20:13:00.921106	2022-11-23 20:13:00.921106	0	8.8
438	3	84	7	4.2	13.15	0	f	2022-11-23 20:16:12.219866	2022-11-23 20:16:12.219866	0	8.95
439	3	82	1	6.1	12.95	0	f	2022-11-23 20:16:12.229146	2022-11-23 20:16:12.229146	-0.1	6.95
440	3	90	3	6.3	14.7	0	f	2022-11-23 20:18:27.138514	2022-11-23 20:18:27.138514	0	8.4
441	3	31	7	4.2	13.35	0	f	2022-11-23 20:19:05.29767	2022-11-23 20:19:05.29767	0	9.15
442	3	74	1	6	13.95	0	f	2022-11-23 20:21:11.873712	2022-11-23 20:21:11.873712	0	7.95
443	3	98	7	4.2	12.75	0	f	2022-11-23 20:22:17.211388	2022-11-23 20:22:17.211388	-0.1	8.65
444	3	75	1	5.7	13.6	0	f	2022-11-23 20:24:19.775254	2022-11-23 20:24:19.775254	-0.2	8.1
445	3	97	7	4.2	13.55	0	f	2022-11-23 20:24:40.391313	2022-11-23 20:24:40.391313	0	9.35
446	3	95	1	5.8	13.2	0	f	2022-11-23 20:32:20.724627	2022-11-23 20:32:20.724627	0	7.4
447	3	83	7	5	14.1	0	f	2022-11-23 20:32:41.009196	2022-11-23 20:32:41.009196	0	9.1
448	3	79	4	4.8	13.6	0	f	2022-11-23 20:33:23.58947	2022-11-23 20:33:23.58947	0	8.8
449	3	86	7	4.2	13.3	0	f	2022-11-23 20:34:50.026582	2022-11-23 20:34:50.026582	0	9.1
450	3	96	1	5.5	14.2	0	f	2022-11-23 20:36:56.305046	2022-11-23 20:36:56.305046	0	8.7
451	3	94	7	4.2	13.3	0	f	2022-11-23 20:37:18.330089	2022-11-23 20:37:18.330089	0	9.1
452	3	92	1	5.4	11.9	0	f	2022-11-23 20:39:53.640135	2022-11-23 20:39:53.640135	-0.1	6.6
453	3	87	7	4.2	13.1	0	f	2022-11-23 20:40:11.147704	2022-11-23 20:40:11.147704	0	8.9
454	3	81	2	5.4	13.75	0	f	2022-11-23 20:41:21.525411	2022-11-23 20:41:21.525411	0	8.35
455	3	93	1	5.7	14.45	0	f	2022-11-23 20:42:59.196353	2022-11-23 20:42:59.196353	0	8.75
456	3	82	2	5.8	14.2	0	f	2022-11-23 20:51:51.237417	2022-11-23 20:51:51.237417	0	8.4
458	3	90	4	5.6	13.9	0	f	2022-11-23 20:53:11.823699	2022-11-23 20:53:11.823699	0	8.3
459	3	74	4	5.6	14.05	0	f	2022-11-23 20:54:49.15227	2022-11-23 20:54:49.15227	-0.1	8.55
460	3	75	2	6.5	13.75	0	f	2022-11-23 20:57:13.939818	2022-11-23 20:57:13.939818	0	7.25
461	3	95	4	5.2	14.1	0	f	2022-11-23 20:58:40.66736	2022-11-23 20:58:40.66736	-0.1	9
462	3	79	5	5.6	13.75	0	f	2022-11-23 21:00:25.183457	2022-11-23 21:00:25.183457	0	8.15
463	3	96	4	5.6	14.3	0	f	2022-11-23 21:01:05.172602	2022-11-23 21:01:05.172602	-0.1	8.8
464	3	92	4	4.8	14.05	0	f	2022-11-23 21:02:12.062038	2022-11-23 21:02:12.062038	0	9.25
465	3	81	5	5.5	13.2	0	f	2022-11-23 21:03:32.031633	2022-11-23 21:03:32.031633	0	7.7
467	3	80	4	4.8	13.95	0	f	2022-11-23 21:06:53.071761	2022-11-23 21:07:30.95244	0	9.15
466	3	93	2	5.6	13.5	0	f	2022-11-23 21:05:45.802858	2022-11-23 21:15:28.058745	0	7.9
468	3	85	8	4.9	11.2	0	f	2022-11-23 21:17:29.223897	2022-11-23 21:17:29.223897	-0.3	6.6
469	3	90	5	5.6	13.95	0	f	2022-11-23 21:18:26.488615	2022-11-23 21:18:26.488615	0	8.35
470	3	84	10	5.1	12.5	0	f	2022-11-23 21:21:20.974302	2022-11-23 21:21:20.974302	0	7.4
471	3	74	5	5.8	13.85	0	f	2022-11-23 21:21:53.289875	2022-11-23 21:21:53.289875	0	8.05
472	3	31	8	5.5	13.55	0	f	2022-11-23 21:23:54.082944	2022-11-23 21:23:54.082944	0	8.05
474	3	95	5	5.5	13.3	0	f	2022-11-23 21:29:52.70831	2022-11-23 21:29:52.70831	0	7.8
475	3	97	10	5.2	13.2	0	f	2022-11-23 21:32:31.314022	2022-11-23 21:32:31.314022	0	8
476	3	79	6	4.9	11.25	0	f	2022-11-23 21:35:11.093588	2022-11-23 21:35:11.093588	0	6.35
477	3	83	8	6	14.25	0	f	2022-11-23 21:36:34.426997	2022-11-23 21:36:34.426997	0	8.25
473	3	75	5	6.3	14.05	0	f	2022-11-23 21:26:55.121964	2022-11-23 21:42:05.230638	0	7.75
478	3	96	5	5.6	14.2	0	f	2022-11-23 21:44:34.863294	2022-11-23 21:44:34.863294	0	8.6
479	3	86	10	5.1	13	0	f	2022-11-23 21:46:34.431959	2022-11-23 21:46:34.431959	0	7.9
480	3	92	5	5.2	13.65	0	f	2022-11-23 21:47:20.099988	2022-11-23 21:47:20.099988	0	8.45
481	3	94	10	5.1	12.4	0	f	2022-11-23 21:50:28.382	2022-11-23 21:50:28.382	-0.1	7.4
482	3	81	6	5.1	13.3	0	f	2022-11-23 21:51:24.131116	2022-11-23 21:51:24.131116	0	8.2
483	3	87	10	4.6	10.8	0	f	2022-11-23 21:53:35.191491	2022-11-23 21:53:35.191491	0	6.2
484	3	93	4	4.8	14	0	f	2022-11-23 21:53:42.827737	2022-11-23 21:53:42.827737	0	9.2
485	3	88	10	4.7	11.7	0	f	2022-11-23 21:56:57.942247	2022-11-23 21:56:57.942247	-0.1	7.1
487	3	82	5	6.3	14.45	0	f	2022-11-23 22:00:23.782822	2022-11-23 22:00:23.782822	0	8.15
488	3	98	10	4.5	10.9	0	f	2022-11-23 22:02:50.881477	2022-11-23 22:02:50.881477	0	6.4
489	3	84	9	5.3	11.6	0	t	2022-11-23 22:15:56.162128	2022-11-23 22:15:56.162128	0	6.3
490	3	75	6	5.8	12.25	0	f	2022-11-23 22:17:36.415406	2022-11-23 22:17:36.415406	0	6.45
491	3	82	4	5.2	14.55	0	f	2022-11-23 22:20:08.141765	2022-11-23 22:20:08.141765	0	9.35
492	3	94	9	5.4	12.75	0	t	2022-11-23 22:20:24.615762	2022-11-23 22:20:24.615762	-0.1	7.45
493	3	86	9	5.6	10.5	0	t	2022-11-23 22:24:34.308842	2022-11-23 22:24:34.308842	-0.1	5
494	3	74	6	6.1	14	0	f	2022-11-23 22:25:48.012465	2022-11-23 22:25:48.012465	0	7.9
495	3	97	9	5.5	12.75	0	t	2022-11-23 22:28:34.336617	2022-11-23 22:28:34.336617	-0.1	7.35
496	3	93	5	6.1	14.15	0	f	2022-11-23 22:29:05.446989	2022-11-23 22:29:05.446989	0	8.05
497	3	31	9	5	11.45	0	t	2022-11-23 22:32:26.936828	2022-11-23 22:32:26.936828	0	6.45
498	3	90	1	5.8	13.2	0	f	2022-11-23 22:34:15.812783	2022-11-23 22:34:15.812783	-0.4	7.8
499	3	83	10	5.4	13.45	0	t	2022-11-23 22:35:52.675644	2022-11-23 22:35:52.675644	0	8.05
500	3	96	3	5.1	13.2	0	f	2022-11-23 22:37:45.885026	2022-11-23 22:37:45.885026	0	8.1
594	4	107	4	5.2	13.45	0	f	2024-11-06 21:30:42.040852	2024-11-06 21:30:42.040852	-0.1	8.35
596	4	117	5	5.7	14.1	0	f	2024-11-06 21:39:12.341936	2024-11-06 21:39:12.341936	0	8.4
598	4	119	5	4.8	12.35	0	f	2024-11-06 21:42:45.851349	2024-11-06 21:42:45.851349	0	7.55
600	4	102	4	5.2	13.7	0	f	2024-11-06 21:46:02.199794	2024-11-06 21:46:02.199794	-0.3	8.8
602	4	103	6	4.2	11.85	0	f	2024-11-06 21:49:58.301937	2024-11-06 21:49:58.301937	0	7.65
604	4	99	5	5.6	12.2	0	f	2024-11-06 21:53:26.232887	2024-11-06 21:53:26.232887	0	6.6
606	4	119	3	5.1	12.6	0	f	2024-11-06 22:05:53.811767	2024-11-06 22:05:53.811767	0	7.5
608	4	102	5	5.4	13.65	0	f	2024-11-06 22:10:20.049363	2024-11-06 22:10:20.049363	0	8.25
610	4	82	5	6.7	15.5	0	f	2024-11-06 22:13:12.649897	2024-11-06 22:13:12.649897	0	8.8
612	4	101	6	5.9	14.05	0	f	2024-11-06 22:15:46.520166	2024-11-06 22:15:46.520166	0	8.15
613	4	118	10	5	12.4	0	f	2024-11-06 22:17:51.858945	2024-11-06 22:17:51.858945	-0.1	7.5
614	4	117	1	5.3	13.4	0	f	2024-11-06 22:19:56.520431	2024-11-06 22:19:56.520431	0	8.1
615	4	120	7	4.2	12.7	0	f	2024-11-06 22:20:50.181142	2024-11-06 22:20:50.181142	-0.3	8.8
616	4	100	6	6.1	12.4	0	f	2024-11-06 22:23:08.200157	2024-11-06 22:23:08.200157	0	6.3
555	4	108	9	5.4	13.1	0	f	2024-11-06 20:14:18.969987	2024-11-06 20:14:18.969987	0	7.7
556	4	116	7	4.2	12.85	0	f	2024-11-06 20:16:40.765359	2024-11-06 20:16:40.765359	0	8.65
557	4	103	4	4.8	13.7	0	f	2024-11-06 20:17:28.583146	2024-11-06 20:17:28.583146	0	8.9
558	4	99	1	5.5	13.85	0	f	2024-11-06 20:18:07.978799	2024-11-06 20:18:07.978799	0	8.35
559	4	109	7	4.2	12.9	0	f	2024-11-06 20:18:40.471985	2024-11-06 20:18:40.471985	0	8.7
560	4	118	7	4.2	13.25	0	f	2024-11-06 20:21:38.805822	2024-11-06 20:21:38.805822	0	9.05
561	4	104	1	5.6	11.65	0	f	2024-11-06 20:21:46.817251	2024-11-06 20:21:46.817251	-0.3	6.35
562	4	101	1	6	13.85	0	f	2024-11-06 20:24:16.744458	2024-11-06 20:24:16.744458	0	7.85
563	4	85	7	4.2	13	0	f	2024-11-06 20:25:08.382735	2024-11-06 20:25:08.382735	0	8.8
564	4	100	3	5.8	14.3	0	f	2024-11-06 20:26:35.974016	2024-11-06 20:26:35.974016	0	8.5
565	4	120	8	6.4	14.9	0	f	2024-11-06 20:33:50.459567	2024-11-06 20:33:50.459567	0	8.5
566	4	82	1	5.9	14.45	0	f	2024-11-06 20:34:58.433045	2024-11-06 20:34:58.433045	0	8.55
567	4	110	9	5.2	12.55	0	f	2024-11-06 20:38:42.998547	2024-11-06 20:38:42.998547	-0.1	7.45
568	4	107	1	5.6	13.5	0	f	2024-11-06 20:39:27.232918	2024-11-06 20:39:27.232918	0	7.9
569	4	94	7	4.2	13.25	0	f	2024-11-06 20:40:17.953574	2024-11-06 20:40:17.953574	0	9.05
570	4	117	2	5.7	13.45	0	f	2024-11-06 20:42:03.095313	2024-11-06 20:42:03.095313	0	7.75
571	4	115	8	4.9	12.7	0	f	2024-11-06 20:43:09.419036	2024-11-06 20:43:09.419036	0	7.8
572	4	119	1	5.7	14.15	0	f	2024-11-06 20:44:52.201852	2024-11-06 20:44:52.201852	0	8.45
573	4	114	8	5.5	12	0	f	2024-11-06 20:46:30.477894	2024-11-06 20:46:30.477894	0	6.5
574	4	102	1	5.6	14.35	0	f	2024-11-06 20:47:58.437144	2024-11-06 20:47:58.437144	0	8.75
575	4	99	4	5.2	13.6	0	f	2024-11-06 20:54:49.857474	2024-11-06 20:54:49.857474	0	8.4
576	4	104	4	5.6	13	0	f	2024-11-06 20:55:56.382389	2024-11-06 20:55:56.382389	-0.3	7.7
577	4	101	3	5.4	13.65	0	f	2024-11-06 20:57:24.539338	2024-11-06 20:57:24.539338	0	8.25
578	4	100	4	5.6	14.35	0	f	2024-11-06 20:58:01.781242	2024-11-06 20:58:01.781242	0	8.75
579	4	82	2	5.7	12.65	0	f	2024-11-06 21:00:57.403484	2024-11-06 21:00:57.403484	0	6.95
580	4	107	2	5.7	12.6	0	f	2024-11-06 21:03:13.288672	2024-11-06 21:03:13.288672	0	6.9
581	4	117	4	5.2	14.3	0	f	2024-11-06 21:04:30.460657	2024-11-06 21:04:30.460657	0	9.1
582	4	119	4	5.2	14.45	0	f	2024-11-06 21:05:34.232762	2024-11-06 21:05:34.232762	0	9.25
584	4	103	5	5.9	12.95	0	f	2024-11-06 21:09:33.024991	2024-11-06 21:09:33.024991	0	7.05
583	4	102	2	5.3	13.15	0	f	2024-11-06 21:08:20.708061	2024-11-06 21:12:26.807427	0	7.85
585	4	116	10	5.1	12.45	0	f	2024-11-06 21:18:02.146612	2024-11-06 21:18:02.146612	0	7.35
586	4	104	5	5.7	14	0	f	2024-11-06 21:18:32.502085	2024-11-06 21:18:32.502085	0	8.3
587	4	109	8	4.8	10.3	0	f	2024-11-06 21:20:45.892735	2024-11-06 21:20:45.892735	0	5.5
588	4	101	4	5.2	14.3	0	f	2024-11-06 21:20:51.129958	2024-11-06 21:20:51.129958	0	9.1
589	4	118	8	5.2	13.3	0	f	2024-11-06 21:22:42.802427	2024-11-06 21:22:42.802427	0	8.1
590	4	100	5	6	14.35	0	f	2024-11-06 21:24:03.907042	2024-11-06 21:24:03.907042	0	8.35
591	4	85	8	4.8	12.55	0	f	2024-11-06 21:25:46.780529	2024-11-06 21:25:46.780529	0	7.75
592	4	82	4	5.2	14.5	0	f	2024-11-06 21:25:55.548657	2024-11-06 21:25:55.548657	0	9.3
\.


--
-- TOC entry 2926 (class 0 OID 24783)
-- Dependencies: 211
-- Data for Name: sport_event; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY public.sport_event (id, location_id, year, name) FROM stdin;
1	1	2016-11-02	Memorial Arturo Gander
2	1	2018-11-14	Memorial Arturo Gander
3	1	2022-11-23	Memorial Arturo Gander
4	1	2024-11-06	Memorial Arturo Gander
\.


--
-- TOC entry 2929 (class 0 OID 24800)
-- Dependencies: 214
-- Data for Name: sport_event_subscriptions; Type: TABLE DATA; Schema: public; Owner: ginnastica_user
--

COPY public.sport_event_subscriptions (id, athlete_id, sport_event_id, final_apparatus_id) FROM stdin;
84	35	1	\N
85	33	1	\N
86	23	1	\N
87	32	1	\N
88	42	1	\N
89	48	1	\N
90	39	1	\N
91	31	1	\N
92	37	1	\N
93	41	1	\N
94	38	1	\N
95	27	1	\N
96	50	1	\N
97	49	1	\N
98	34	1	\N
99	36	1	\N
100	44	1	\N
101	47	1	\N
102	40	1	\N
103	46	1	\N
104	23	2	\N
105	32	2	\N
106	58	2	\N
108	53	2	\N
109	49	2	\N
110	54	2	\N
111	36	2	\N
112	55	2	\N
113	56	2	\N
114	57	2	\N
115	33	2	\N
116	59	2	\N
118	31	2	\N
119	41	2	\N
121	62	2	\N
123	66	2	\N
125	64	2	\N
126	65	2	\N
127	67	2	\N
128	39	2	\N
129	68	2	\N
175	74	3	\N
176	75	3	\N
179	80	3	\N
180	79	3	\N
181	81	3	\N
182	82	3	\N
186	84	3	\N
187	85	3	\N
188	86	3	\N
189	87	3	\N
191	88	3	\N
193	90	3	\N
199	31	3	\N
200	94	3	\N
201	92	3	\N
202	93	3	\N
203	83	3	\N
204	97	3	\N
205	98	3	\N
206	95	3	\N
207	96	3	\N
224	109	4	\N
225	99	4	\N
226	100	4	\N
227	101	4	\N
228	102	4	\N
229	82	4	\N
230	103	4	\N
231	104	4	\N
234	107	4	\N
235	108	4	\N
236	110	4	\N
239	94	4	\N
240	114	4	\N
241	115	4	\N
242	116	4	\N
243	117	4	\N
244	85	4	\N
246	118	4	\N
247	119	4	\N
248	120	4	\N
\.


--
-- TOC entry 2960 (class 0 OID 0)
-- Dependencies: 202
-- Name: apparatus_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('public.apparatus_seq', 10, true);


--
-- TOC entry 2961 (class 0 OID 0)
-- Dependencies: 204
-- Name: athlete_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('public.athlete_seq', 120, true);


--
-- TOC entry 2962 (class 0 OID 0)
-- Dependencies: 212
-- Name: city_cup_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('public.city_cup_seq', 1, false);


--
-- TOC entry 2963 (class 0 OID 0)
-- Dependencies: 216
-- Name: location_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('public.location_seq', 1, true);


--
-- TOC entry 2964 (class 0 OID 0)
-- Dependencies: 208
-- Name: scores_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('public.scores_seq', 616, true);


--
-- TOC entry 2965 (class 0 OID 0)
-- Dependencies: 210
-- Name: sport_event_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('public.sport_event_seq', 1, true);


--
-- TOC entry 2966 (class 0 OID 0)
-- Dependencies: 213
-- Name: sport_event_subscriptions_seq; Type: SEQUENCE SET; Schema: public; Owner: ginnastica_user
--

SELECT pg_catalog.setval('public.sport_event_subscriptions_seq', 248, true);


--
-- TOC entry 2764 (class 2606 OID 24833)
-- Name: apparatus apparatus_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.apparatus
    ADD CONSTRAINT apparatus_id_pk PRIMARY KEY (id);


--
-- TOC entry 2766 (class 2606 OID 24835)
-- Name: athlete athlete_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.athlete
    ADD CONSTRAINT athlete_id_pk PRIMARY KEY (id);


--
-- TOC entry 2776 (class 2606 OID 24839)
-- Name: location location_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.location
    ADD CONSTRAINT location_id_pk PRIMARY KEY (id);


--
-- TOC entry 2768 (class 2606 OID 24841)
-- Name: nations nation_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.nations
    ADD CONSTRAINT nation_pk PRIMARY KEY (id);


--
-- TOC entry 2770 (class 2606 OID 24843)
-- Name: scores scores_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.scores
    ADD CONSTRAINT scores_id_pk PRIMARY KEY (id);


--
-- TOC entry 2772 (class 2606 OID 24845)
-- Name: sport_event sport_event_id_pk; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.sport_event
    ADD CONSTRAINT sport_event_id_pk PRIMARY KEY (id);


--
-- TOC entry 2774 (class 2606 OID 24847)
-- Name: sport_event_subscriptions sport_event_subscriptions_pkey; Type: CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.sport_event_subscriptions
    ADD CONSTRAINT sport_event_subscriptions_pkey PRIMARY KEY (id);


--
-- TOC entry 2785 (class 2620 OID 24848)
-- Name: scores sync_modification_date; Type: TRIGGER; Schema: public; Owner: ginnastica_user
--

CREATE TRIGGER sync_modification_date BEFORE INSERT OR UPDATE ON public.scores FOR EACH ROW EXECUTE FUNCTION public.sync_modification_date_fn();


--
-- TOC entry 2778 (class 2606 OID 24854)
-- Name: scores apparatus_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.scores
    ADD CONSTRAINT apparatus_id_fk FOREIGN KEY (apparatus_id) REFERENCES public.apparatus(id);


--
-- TOC entry 2779 (class 2606 OID 24859)
-- Name: scores athlete_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.scores
    ADD CONSTRAINT athlete_id_fk FOREIGN KEY (athlete_id) REFERENCES public.athlete(id);


--
-- TOC entry 2781 (class 2606 OID 24864)
-- Name: sport_event location_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.sport_event
    ADD CONSTRAINT location_id_fk FOREIGN KEY (location_id) REFERENCES public.location(id);


--
-- TOC entry 2777 (class 2606 OID 24869)
-- Name: athlete nation_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.athlete
    ADD CONSTRAINT nation_id_fk FOREIGN KEY (nation_id) REFERENCES public.nations(id) ON UPDATE CASCADE;


--
-- TOC entry 2784 (class 2606 OID 24874)
-- Name: location nation_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.location
    ADD CONSTRAINT nation_id_fk FOREIGN KEY (nation_id) REFERENCES public.nations(id);


--
-- TOC entry 2780 (class 2606 OID 24884)
-- Name: scores sport_event_id_fk; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.scores
    ADD CONSTRAINT sport_event_id_fk FOREIGN KEY (sport_event_id) REFERENCES public.sport_event(id);


--
-- TOC entry 2782 (class 2606 OID 24889)
-- Name: sport_event_subscriptions sport_event_subscriptions_athlete_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.sport_event_subscriptions
    ADD CONSTRAINT sport_event_subscriptions_athlete_id_fkey FOREIGN KEY (athlete_id) REFERENCES public.athlete(id);


--
-- TOC entry 2783 (class 2606 OID 24894)
-- Name: sport_event_subscriptions sport_event_subscriptions_sport_event_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: ginnastica_user
--

ALTER TABLE ONLY public.sport_event_subscriptions
    ADD CONSTRAINT sport_event_subscriptions_sport_event_id_fkey FOREIGN KEY (sport_event_id) REFERENCES public.sport_event(id);


--
-- TOC entry 2938 (class 0 OID 0)
-- Dependencies: 4
-- Name: SCHEMA public; Type: ACL; Schema: -; Owner: postgres
--

GRANT ALL ON SCHEMA public TO PUBLIC;
GRANT USAGE ON SCHEMA public TO ginnastica_readonly;


--
-- TOC entry 2940 (class 0 OID 0)
-- Dependencies: 202
-- Name: SEQUENCE apparatus_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON SEQUENCE public.apparatus_seq TO ginnastica_readonly;


--
-- TOC entry 2941 (class 0 OID 0)
-- Dependencies: 203
-- Name: TABLE apparatus; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.apparatus TO ginnastica_readonly;


--
-- TOC entry 2942 (class 0 OID 0)
-- Dependencies: 204
-- Name: SEQUENCE athlete_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON SEQUENCE public.athlete_seq TO ginnastica_readonly;


--
-- TOC entry 2943 (class 0 OID 0)
-- Dependencies: 205
-- Name: TABLE athlete; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.athlete TO ginnastica_readonly;


--
-- TOC entry 2944 (class 0 OID 0)
-- Dependencies: 206
-- Name: TABLE nations; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.nations TO ginnastica_readonly;


--
-- TOC entry 2945 (class 0 OID 0)
-- Dependencies: 207
-- Name: TABLE athlete_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.athlete_vw TO ginnastica_readonly;


--
-- TOC entry 2946 (class 0 OID 0)
-- Dependencies: 208
-- Name: SEQUENCE scores_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON SEQUENCE public.scores_seq TO ginnastica_readonly;


--
-- TOC entry 2947 (class 0 OID 0)
-- Dependencies: 209
-- Name: TABLE scores; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.scores TO ginnastica_readonly;


--
-- TOC entry 2948 (class 0 OID 0)
-- Dependencies: 210
-- Name: SEQUENCE sport_event_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON SEQUENCE public.sport_event_seq TO ginnastica_readonly;


--
-- TOC entry 2949 (class 0 OID 0)
-- Dependencies: 211
-- Name: TABLE sport_event; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.sport_event TO ginnastica_readonly;


--
-- TOC entry 2950 (class 0 OID 0)
-- Dependencies: 221
-- Name: TABLE chrono_list_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.chrono_list_vw TO ginnastica_readonly;


--
-- TOC entry 2951 (class 0 OID 0)
-- Dependencies: 212
-- Name: SEQUENCE city_cup_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON SEQUENCE public.city_cup_seq TO ginnastica_readonly;


--
-- TOC entry 2952 (class 0 OID 0)
-- Dependencies: 213
-- Name: SEQUENCE sport_event_subscriptions_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON SEQUENCE public.sport_event_subscriptions_seq TO ginnastica_readonly;


--
-- TOC entry 2953 (class 0 OID 0)
-- Dependencies: 214
-- Name: TABLE sport_event_subscriptions; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.sport_event_subscriptions TO ginnastica_readonly;


--
-- TOC entry 2954 (class 0 OID 0)
-- Dependencies: 215
-- Name: TABLE event_athlete_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.event_athlete_vw TO ginnastica_readonly;


--
-- TOC entry 2955 (class 0 OID 0)
-- Dependencies: 216
-- Name: SEQUENCE location_seq; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON SEQUENCE public.location_seq TO ginnastica_readonly;


--
-- TOC entry 2956 (class 0 OID 0)
-- Dependencies: 217
-- Name: TABLE location; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.location TO ginnastica_readonly;


--
-- TOC entry 2957 (class 0 OID 0)
-- Dependencies: 220
-- Name: TABLE ranking_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.ranking_vw TO ginnastica_readonly;


--
-- TOC entry 2958 (class 0 OID 0)
-- Dependencies: 219
-- Name: TABLE scores_male_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.scores_male_vw TO ginnastica_readonly;


--
-- TOC entry 2959 (class 0 OID 0)
-- Dependencies: 218
-- Name: TABLE total_scores_vw; Type: ACL; Schema: public; Owner: ginnastica_user
--

GRANT SELECT ON TABLE public.total_scores_vw TO ginnastica_readonly;


--
-- TOC entry 1752 (class 826 OID 24899)
-- Name: DEFAULT PRIVILEGES FOR TABLES; Type: DEFAULT ACL; Schema: public; Owner: postgres
--

ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public REVOKE ALL ON TABLES  FROM postgres;
ALTER DEFAULT PRIVILEGES FOR ROLE postgres IN SCHEMA public GRANT SELECT ON TABLES  TO ginnastica_readonly;


-- Completed on 2024-11-13 08:25:51

--
-- PostgreSQL database dump complete
--

--
-- Database "postgres" dump
--

\connect postgres

--
-- PostgreSQL database dump
--

-- Dumped from database version 12.1
-- Dumped by pg_dump version 12.1

-- Started on 2024-11-13 08:25:52

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 1 (class 3079 OID 16384)
-- Name: adminpack; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;


--
-- TOC entry 2813 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION adminpack; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';


-- Completed on 2024-11-13 08:25:52

--
-- PostgreSQL database dump complete
--

-- Completed on 2024-11-13 08:25:52

--
-- PostgreSQL database cluster dump complete
--

