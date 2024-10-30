package br.com;

import java.io.Serializable;
import java.time.LocalDate;

public class Pessoa implements Serializable {

    private String nome;
    private String profissao;
    private LocalDate dataNascimento;
    private transient int idade;

    
}
