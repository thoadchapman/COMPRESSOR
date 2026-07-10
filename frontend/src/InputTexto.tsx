import { useComp } from './useComp';
import { useApp } from './AppContext';

type InputTextoProps = {
    texto: string;
    setTexto: (e: string) => void;
};

export default function InputTexto({ texto, setTexto }: InputTextoProps) {
    const { setOriginalString } = useApp();
    const comp = useComp();

    const handlePressTexto = async (e: React.KeyboardEvent<HTMLInputElement>) => {
        if (e.key === 'Enter') {
            e.preventDefault();
            if (texto?.trim()) {
                setOriginalString(texto);
                await comp('COMPRIMIR', texto);
            }
        }
    };

    return (
        <div className="input-container">
            <input
                type="text"
                placeholder="digite para comprimir..."
                value={texto}
                onChange={e => setTexto(e.target.value)}
                onKeyDown={handlePressTexto}
                className="custom-input"
            />
        </div>
    );
}