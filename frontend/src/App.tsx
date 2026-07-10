import { useState } from 'react';
import { Modo } from './Modo';
import Resultado from './Resultado';
import InputArquivo from './inputArquivo';
import InputTexto from './inputTexto';
import './App.css';


function App() {
    const [texto, setTexto] = useState('');
    const [arquivo, setArquivo] = useState<File | null>(null);
    const [modo, setModo] = useState<Modo | null>(null);
    return (
        <div className='porra-toda'>
            <h1>compressor.</h1>
            <InputTexto
                texto={texto}
                setTexto={setTexto}
            />
            <InputArquivo
                setArquivo={setArquivo}
            />
            <Resultado />
        </div>
    );
}

export default App;