import { useState } from 'react';
import { useComp } from './comp';
import { useApp } from './AppContext';
import Resultado from './Resultado';
import './App.css';

function App() {
    const [texto, setTexto] = useState('');
    const [arquivo, setArquivo] = useState(null);
    const { setOriginal } = useApp();
    const comp = useComp();

    const handlePressTexto = async (e) => {
        if (e.key === 'Enter') {
            e.preventDefault();
            if (texto?.trim()) {
                setOriginal(texto);
                await comp('COMPRIMIR', texto);
            }
        }
    };
    const handleFileChange = (e) => {
        const file = e.target.files[0];
        if (!file) return;
        setArquivo(file);
        setOriginal(file);
        const reader = new FileReader();
        reader.onload = async (event) => {
            const arrayBuffer = event.target.result;
            const uint8Array = new Uint8Array(arrayBuffer);
            const base64 = btoa(String.fromCharCode(...uint8Array));
            await comp('COMPRIMIR', base64);
        };
        reader.readAsArrayBuffer(file);
    };
    return (
        <div className='porra-toda'>
            <h1>compressor.</h1>
            <div className="input-container">
                <input
                    type="text"
                    placeholder="digite para comprimir..."
                    value={texto}
                    onChange={e => setTexto(e.target.value)}
                    onKeyDown={handlePressTexto}
                    className="custom-input"
                />
                <input
                    type="file"
                    placeholder="escolha para comprimir..."
                    onChange={handleFileChange}
                    className="custom-input"
                />
            </div>
            <Resultado />
        </div>
    );
}

export default App;