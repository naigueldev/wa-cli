# 🧠 wa — ChatGPT no Terminal com Simplicidade

`wa` é uma mini ferramenta de linha de comando (CLI) feita em C que te permite conversar com o ChatGPT direto pelo terminal Linux de forma rápida, leve e prática. Basta digitar `wa <sua mensagem>` e receber a resposta da IA direto na tela.

> Ideal para devs, estudantes ou entusiastas que querem uma resposta rápida sem abrir o navegador.

---

## 🚀 Como funciona?

Você digita algo assim:

```bash
wa "me explique como funciona o protocolo TCP"
```

E o `wa` faz uma requisição para a API da OpenAI (ChatGPT) e imprime a resposta formatada direto no terminal.

---

## ⚙️ Requisitos

- Linux com suporte a `curl`
- Compilador C (`gcc`)
- Chave de API da OpenAI (crie em: [https://platform.openai.com/account/api-keys](https://platform.openai.com/account/api-keys))

---

## 🔐 Configurando a chave da API

**Você deve definir a chave como variável de ambiente:**

```bash
export OPENAI_API_KEY="sua-api-key-aqui"
```

Para definir isso automaticamente em cada terminal, adicione essa linha no seu `~/.bashrc`, `~/.zshrc` ou equivalente:

```bash
echo 'export OPENAI_API_KEY="sua-api-key-aqui"' >> ~/.bashrc
source ~/.bashrc
```

---

## 🛠️ Compilação

Clone o projeto (ou crie o `wa.c`) e compile com:

```bash
gcc wa.c -o wa -lcurl
```

Se tudo estiver certo, o binário `wa` estará pronto.

---

## 📦 Instalação (opcional)

Se quiser usar `wa` como um comando global:

```bash
sudo mv wa /usr/local/bin/
```

Agora você pode rodar de qualquer lugar:

```bash
wa "quem foi Alan Turing?"
```

---

## 📋 Exemplo de uso

```bash
$ wa "explique o paradoxo dos gêmeos"
Resposta do ChatGPT:
O paradoxo dos gêmeos é um experimento mental da teoria da relatividade...
```

---

## 🧩 Estrutura interna

O `wa`:
- Lê sua mensagem do terminal.
- Formata a mensagem como um JSON válido para a API.
- Faz uma requisição HTTP POST para `https://api.openai.com/v1/chat/completions`.
- Imprime a resposta formatada no terminal.

---

## 🧪 Dicas e Testes

- Funciona bem para mensagens curtas e objetivas.
- Para mensagens com múltiplas palavras, use aspas:
  ```bash
  wa "resuma a revolução francesa"
  ```

---

## 💡 Sugestões futuras

- Salvar histórico local de perguntas/respostas.
- Suporte a modelos customizados.
- Interface interativa no terminal (modo chat).

---

## 📜 Licença

Este projeto é open source e livre para modificação e uso pessoal.

---

Feito com ☕, C e API da OpenAI.