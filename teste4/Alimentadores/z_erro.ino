//Aqui vai tudo relacionado ao codigo de erro enviado no pacote

/*Estrutura do pacote a ser enviado
erro:
   Dec ||    Bin   ||  Código
    1: ||      1   ||  Dados recebidos inconpativeis
    2: ||     10   ||  Tempo de alimentação muito grande
    4: ||    100   ||  Porta do alimntador com defeito
    8: ||   1000   ||  Tampa do reservatório aberta
   16: ||  10000   ||  Erro ao medir nivel
   32; || 100000   || 
   
*/

void cod_erro(){
  erro = 0;

////////////////////// tampa aberta  
     int tampatemp = digitalRead(tampa);
     if(tampatemp == HIGH) { 
         erro = erro + 8;         
//        Serial.println("    a porta esta aberta      "); 
     } else {
//        Serial.println(" nao esta mais kkkkkkk  "); 
     }


////////////////////// erro ao medir nivel de raçao
     if(erro_nivel == true) { 
      erro = erro + 16;
     }


     
/////////////////////  Tempo de alimentação muito grande   
//     int rotfusotemp = digitalRead(rotfuso);

// se o tempo de 0 para 1 ou de 1 para 0 for maior que 1 segundo o motor esta parado..
    

}


