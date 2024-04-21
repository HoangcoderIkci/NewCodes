alphabet = [' ','А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ь','Ы', 'Ъ', 'Э', 'Ю', 'Я']
dict_alphabet = dict(zip(alphabet, list(range(len(alphabet)))))
gamma = "СТЫЬБВДАЗЕГЫПАФЫМСУП КЬТП ЛВХУЩЕШГНЬИТКЖФХЙЧЧЫВЦКИ"
print(dict_alphabet)
N = 33
def encrypt(text):
    encryptedText = ""
    for i in range(len(text)):
        encryptedText += alphabet[(dict_alphabet[text[i]]+dict_alphabet[gamma[i]])%N]
    print(encryptedText)
T4 = "НАМ ДОВОЛЬНО ПРОЗРАЧНО НАМЕКНУЛИЗПТ ЧТОБЫ МЫ НЕПОК"
print("t4",T4[22])
T5 = "Я ВЫЛЕЗЛА ИЗ ОКНА ВАННОЙ ИСПУСТИЛАСЬ ПО ВОДОСТОЧНО"
print("t5",T5[22])

encrypt(T4)

word = "ЧТОБЫ "
S1 = "юмыизвсполрыясэзхюфбькиьыацлкуйлриьгтынщфдшбшыръьщ"
S1 = S1.upper()
S2 = "цаэйнютпзчмжябжвгянщ яжшуммхюкж бгтбо ртпбпдяйхцыч"
S2 = S2.upper()

S3 = "ртэгжирбзлзипохйштегоьзшпсялвябкаснмоцмлбфйыэсижщх"
S3 = S3.upper()
S4 = "яужьжсзпуасипрдифбфжнщь рмснвждо у ь дмиохцсчзиещу"
S4 = S4.upper()
print("t4",S4[22])
S5 = "ртэхниммиембппязнсцрншйъпиэтидлогдяцибмжчгоеимсншч"
S5 = S5.upper()
print("t4",S5[22])

def subString(S1,S2):
    return [(dict_alphabet[S1[i]]-dict_alphabet[S2[i]])%N for i in range(len(S1))]
H1 = subString(T4,T5)
H2 = subString(S4,S5)
for i in range(len(H1)):
    if H1[i] != H2[i]:
        print(i,H1[i],H2[i])

H = [dict_alphabet[S3[i]]-dict_alphabet[S4[i]] for i in range(len(S1))]
# H2 = [dict_alphabet[S3[i]]-dict_alphabet[S5[i]] for i in range(len(S1))]

newWords = ""
print(H)
with open('E:\\StoreCode\\CodeVSCode\\cipher\\res.txt', 'a',encoding="utf-8") as file:
    for id in range(len(H)-len(word)):
        newWords = ""
        for id2,elem in  enumerate(word):
            newWords += alphabet[(dict_alphabet[elem] + H[id+id2])%N]
            #newWords += chr(ord(word[id2]) + elem)
        #file.write(newWords+",")
        print(newWords,end=",")