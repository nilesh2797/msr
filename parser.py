import urllib
import sys
import codecs
import py_stringmatching as sm
from bs4 import BeautifulSoup

import os

directory = "Sandbox/Data/Wiki10_RawData/"
num_parsed = 0

for filename in os.listdir(directory):
	file = os.path.join(directory, filename)

	html = urllib.urlopen(file).read()
	soup = BeautifulSoup(html)

	for script in soup(["script", "style"]):
		script.extract()

	text = soup.get_text()

	lines = (line.strip() for line in text.splitlines())
	chunks = (phrase.strip() for line in lines for phrase in line.split("  "))
	unicodetext = '\n'.join(chunk for chunk in chunks if chunk)

	import unicodedata
	text = unicodedata.normalize('NFKD', unicodetext).encode('ascii','ignore')

	alnum_tok = sm.AlphanumericTokenizer()
	tokenized_words = alnum_tok.tokenize(text)

	from nltk.stem import PorterStemmer
	from nltk.tokenize import sent_tokenize, word_tokenize

	ps = PorterStemmer()

	bag = {}
	for w in tokenized_words:
		stemw = ps.stem(w)
		if stemw not in bag:
			bag[stemw] = 1
		else:
			bag[stemw] += 1

	from nltk.corpus import stopwords 

	stop_words = set(stopwords.words('english')) 
	# filtered_bag = [w for w in word_tokens if not w in stop_words]

	for stopw in stop_words:
		if stopw in bag:
			del bag[stopw]

	import sys

	for token in bag:
		sys.stdout.write(token+":"+str(bag[token])+" ")
	sys.stdout.write("\n")

	num_parsed += 1
	if num_parsed >= 1000:
		break
