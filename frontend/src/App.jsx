import { useState } from 'react';
import { useApp } from './AppContext';
import { useCompDescomp } from './compDescomp';
import Resultado from './Resultado';
import './App.css';

function App() {
    const [texto, setTexto] = useState('');
    const { compressa } = useApp();
    const compDescomp = useCompDescomp();

    const handlePress = async (e) => {
        if (e.key === 'Enter') {
            e.preventDefault();
            if (texto?.trim()) {
                await compDescomp(true, texto);
            }
        }
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
                    onKeyDown={handlePress}
                    className="custom-input"
                />
            </div>
            <Resultado />
        </div>
    );
}

export default App;