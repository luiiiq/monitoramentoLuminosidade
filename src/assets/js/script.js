const botaoConectar = document.querySelector("#conectar");
const imgs = document.querySelectorAll(".painelIntro img");
const imgsLeds = document.querySelectorAll(".leds img");
const painel = document.querySelector(".painelPrincipal");
const porcentagem = document.querySelector(".porcentagem");
const progresso = document.querySelector(".progresso");
const statusSpan = document.querySelector(".status span");
const led = document.querySelector(".corLed");

botaoConectar.addEventListener("click", async () => {
    try {
        // Conecta ao Arduino
        const porta = await navigator.serial.requestPort();

        // Abre a conexão
        await porta.open({ baudRate: 9600 });

        // Transforma os dados recebidos em texto
        const decoder = new TextDecoderStream();

        porta.readable.pipeTo(decoder.writable);

        // Permite ler os dados recebidos
        const leitor = decoder.readable.getReader();

        let dadosRecebidos = "";

        while (true) {
            const { value, done } = await leitor.read();

            if (done) break;

            dadosRecebidos += value;

            // Separa os dados por linha
            const linhas = dadosRecebidos.split("\n");
            dadosRecebidos = linhas.pop();

            // Lê cada linha recebida
            for (const linha of linhas) {
                try {
                    // Converte o texto em dados JavaScript
                    const dados = JSON.parse(linha.trim());
                    porcentagem.textContent = dados.porcentagem;
                    progresso.style.setProperty
                    (
                        "--progresso-width",
                        dados.porcentagem + "%"
                    );

                    if (dados.estado == "VERDE") {
                        painel.classList.add("verde");
                        painel.classList.remove("amarelo");
                        painel.classList.remove("vermelho");
                        statusSpan.textContent = "OK";
                        led.textContent = "VERDE";

                        imgs.forEach((img) => {
                            if (img.id == "verde") {
                                img.classList.add("ativo");
                            }
                            else {
                                img.classList.remove("ativo");
                            }
                        });
                        imgsLeds.forEach((img) => {
                            if (img.id == "verde") {
                                img.classList.add("ligado");
                            }
                            else {
                                img.classList.remove("ligado");
                            }
                        });
                    }
                    else if (dados.estado == "AMARELO") {
                        painel.classList.remove("verde");
                        painel.classList.add("amarelo");
                        painel.classList.remove("vermelho");
                        statusSpan.textContent = "Alerta";
                        led.textContent = "AMARELO";

                        imgs.forEach((img) => {
                            if (img.id == "amarelo") {
                                img.classList.add("ativo");
                            }
                            else {
                                img.classList.remove("ativo");
                            }
                        });
                        imgsLeds.forEach((img) => {
                            if (img.id == "amarelo") {
                                img.classList.add("ligado");
                            }
                            else {
                                img.classList.remove("ligado");
                            }
                        });

                    } else {
                        painel.classList.remove("verde");
                        painel.classList.remove("amarelo");
                        painel.classList.add("vermelho");
                        statusSpan.textContent = "ERROR!";
                        led.textContent = "VERMELHO";
                        imgs.forEach((img) => {
                            if (img.id == "vermelho") {
                                img.classList.add("ativo");
                            }
                            else {
                                img.classList.remove("ativo");
                            }
                        });
                        imgsLeds.forEach((img) => {
                            if (img.id == "vermelho") {
                                img.classList.add("ligado");
                            }
                            else {
                                img.classList.remove("ligado");
                            }
                        });
                    }
                } catch (erro) {
                    console.log("Linha ignorada:", linha);
                }
            }
        }

    } catch (erro) {
        // Mostra uma mensagem caso ocorra um erro
        console.error("Erro ao conectar:", erro);
    }
});